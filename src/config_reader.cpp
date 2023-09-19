#include "config_reader.h"
#include <iostream>
#include <algorithm>

size_t snake::findNameOfVaribale(std::string_view& str, size_t start_pos) {
    size_t pos_first = str.find_first_not_of(' ', start_pos);                                      // первый символ названия переменной
    size_t pos_equal = str.find_first_of('=', pos_first);                                          // первый знак =
    size_t pos_last = str[pos_equal - 1] == ' ' ? str.find_first_of(' ', pos_first) : (pos_equal); // последний знак имени переменной
    
    // Будем возвращать первый символ после знака '=' не равный пробелу
    pos_equal = str.find_first_not_of(' ', ++pos_equal);

    str.remove_prefix(std::min(pos_first, str.size()));
    str.remove_suffix(std::min(str.size() - pos_last + pos_first, str.size()));
    return pos_equal;
}

size_t snake::findValue(std::string_view &str, size_t start_pos) {
    size_t pos_first = str.find_first_not_of(' ', start_pos);    // ищем первый и последний символ значения переменной
    size_t pos_last = str.find_first_of(" ,}", start_pos);       // 
    size_t returned_pos = str.find_first_not_of(" ", pos_last);  // возвращать будем позицию первого символа после значения переменной не равный пробелу

    str.remove_prefix(std::min(pos_first, str.size()));
    str.remove_suffix(std::min(str.size() - pos_last + pos_first, str.size()));
    return returned_pos;
}

size_t snake::findStringValue(std::string_view& str, size_t start_pos) {
    size_t pos_first = start_pos + 1;  // находим первую и последнюю ковычку 
    size_t pos_last = str.find_first_of('\"', pos_first); 
    size_t returned_pos = str.find_first_not_of(" ,", ++pos_last); //  возвращать будем позицию первого символа после '\"' не равный пробелу

    str.remove_prefix(std::min(pos_first, str.size()));
    str.remove_suffix(std::min(str.size() - pos_last + 1 + pos_first, str.size()));

    return returned_pos;
}

std::string snake::combineSettingsIntoOneLine(std::ifstream &file) {
    std::string settings;
    std::string line;
    while (std::getline(file, line)) {
        settings += line;
        settings += " "; // пробел для отделения значения от имени
    }
    return settings;
}

snake::Data snake::ParseName(std::string_view str, size_t& start_pos) {
    start_pos = findNameOfVaribale(str, start_pos);
    return Data(std::string(str));
}

snake::Data snake::ParseStringValue(std::string_view str, size_t& start_pos) {
    start_pos = findStringValue(str, start_pos);
    return Data(std::string(str));
}

snake::Data snake::ParseValue(std::string_view str, size_t& start_pos) {
    start_pos = findValue(str, start_pos);
    return Data(std::string(str));
}

std::vector<snake::Data> snake::ParseArray(std::string_view str, size_t& start_pos) {
    std::vector<snake::Data> arr;
    start_pos = str.find_first_not_of("{ ", start_pos);

    while(str[start_pos] != '}' && start_pos != str.npos) {
        if (str[start_pos] == '\"') {
            arr.push_back(ParseStringValue(str, start_pos));
        } else {
            arr.push_back(ParseValue(str, start_pos));
        }
        // Если после символа идёт знак '=', то парсим значения для вложенного массива 
        if (str[start_pos] == '=') {
            start_pos = str.find_first_not_of("= ", start_pos);
            std::vector<Data> value_arr = ParseArray(str, start_pos);
            for (Data& value : value_arr) {
                arr.back().addValue(std::make_shared<Data>(value));
            }  
        } 
        start_pos = str.find_first_not_of(" ,", start_pos);
    }
    start_pos = str.find_first_not_of("} ", start_pos);
    return arr;
}

std::vector<snake::Data> snake::ParseSetting(std::ifstream& file) {
    std::string settings(std::move(combineSettingsIntoOneLine(file)));
    std::string_view setting_view(settings);
    std::vector<Data> result;

    size_t start_pos = 0;

    while (start_pos != setting_view.npos) {
        // Ищу название переменной
        result.push_back(ParseName(setting_view, start_pos)); // start_pos - указывает на первый символ после '='
                                                              // не равный пробелу
        // В зависиости от символа после знака '=' выбираем тип переменной для парсинга
        if (setting_view[start_pos] == '\"') {
            // парсим строку
            // после выполнения start_pos - указывает на первый символ после '\"' не равный пробелу
            result.back().addValue(std::make_shared<Data>(ParseStringValue(setting_view, start_pos)));
        } else if (setting_view[start_pos] == '{') {
            // парсим массив
            auto arr = ParseArray(setting_view, start_pos); // выделяем массив значений
            for (Data& value : arr) {
                result.back().addValue(std::make_shared<Data>(value)); // добавлям весь массив значений
            }
            start_pos = setting_view.find_first_not_of(" }", start_pos);
        } else {
            // парсим простое значение
            // после выполнения start_pos - указывает на первый символ не равный пробелу
            result.back().addValue(std::make_shared<Data>(ParseValue(setting_view, start_pos)));
        }
    }

    return result;
}

snake::Data::Data(std::string name)
    : _name_var(name) {
}

void snake::Data::addValue(std::shared_ptr<Data> value) {
    _value.push_back(value);
}

snake::ConfigReader::ConfigReader(const std::string& file_name)
    : _file(std::move(file_name))
    , _settings(ParseSetting(_file)) {
    if (!_file.is_open()) {
        std::cerr << "Fatal error: file is could't be opened" << std::endl;
    }
}

std::ifstream &snake::ConfigReader::getFile() {
    return _file;
}

std::vector<snake::Data>& snake::ConfigReader::getAllSettings() {
    return _settings;
}

std::vector<std::shared_ptr<snake::Data>>& snake::ConfigReader::findSetting(const std::string& name_of_setting) {
    auto it = std::find_if(_settings.begin(), _settings.end(), [&name_of_setting](Data& data) {
        return data._name_var == name_of_setting;
    });
    return it->_value;
}