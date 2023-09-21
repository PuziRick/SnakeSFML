#include "config_reader.h"
#include <algorithm>
#include <iostream>

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
    size_t pos_first = str.find_first_not_of(" ,", start_pos);    // ищем первый и последний символ значения переменной
    size_t pos_last = str.find_first_of(" ,}=", start_pos);       // 
    size_t returned_pos = str.find_first_not_of(" ", pos_last);   // возвращать будем позицию первого символа после значения переменной не равный пробелу
    
    str.remove_prefix(std::min(pos_first, str.size()));
    str.remove_suffix(std::min(str.size() - pos_last + pos_first, str.size()));

    return returned_pos;
}

size_t snake::findStringValue(std::string_view& str, size_t start_pos) {
    size_t pos_first = start_pos + 1;                              // находим первую и последнюю ковычку 
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

snake::SettingsData snake::ParseName(std::string_view str, size_t& start_pos) {
    start_pos = findNameOfVaribale(str, start_pos);
    return SettingsData(std::string(str));
}

snake::SettingsData snake::ParseStringValue(std::string_view str, size_t& start_pos) {
    start_pos = findStringValue(str, start_pos);
    return SettingsData(std::string(str));
}

snake::SettingsData snake::ParseValue(std::string_view str, size_t& start_pos) {
    start_pos = findValue(str, start_pos);
    return SettingsData(std::string(str));
}

// Рекурсивная функция для парсиная массива
void snake::ParseArray(std::string_view str, size_t &start_pos, SettingsData &header) {
    // условие выхода из рекурсии символ '}' (конец массива) или конец документа npos
    if (str[start_pos] == '}' || start_pos == str.npos) {
        ++start_pos;
        start_pos = str.find_first_not_of(" ", start_pos);
        return;
    }
    // выбор типа переменной для парсинга
    if (str[start_pos] == '\"') {
        header.addValue(std::make_shared<SettingsData>(ParseStringValue(str, start_pos)));
    } else {
        header.addValue(std::make_shared<SettingsData>(ParseValue(str, start_pos)));
    }
    // парсим название  подмассива (если он есть)
    if (str[start_pos] == '=') {
        start_pos = str.find_first_not_of("= {", start_pos);
        ParseArray(str, start_pos, *header._value.back());
    }
    start_pos = str.find_first_not_of(", {", start_pos);
    ParseArray(str, start_pos, header);
}

std::vector<snake::SettingsData> snake::ParseSetting(std::ifstream& file) {
    std::string settings(std::move(combineSettingsIntoOneLine(file)));
    std::string_view setting_view(settings);
    std::vector<SettingsData> result;

    size_t start_pos = 0;

    while (start_pos != setting_view.npos) {
        // Ищу название переменной
        result.push_back(ParseName(setting_view, start_pos)); // start_pos - указывает на первый символ после '='
                                                              // не равный пробелу
        // В зависиости от символа после знака '=' выбираем тип переменной для парсинга
        if (setting_view[start_pos] == '\"') {
            // парсим строку
            // после выполнения start_pos - указывает на первый символ после '\"' не равный пробелу
            result.back().addValue(std::make_shared<SettingsData>(ParseStringValue(setting_view, start_pos)));
        } else if (setting_view[start_pos] == '{') {
            // парсим массив
            // после выполнения start_pos - указывает на первый символ после '}' не равынй пробелу
            start_pos = setting_view.find_first_not_of("{ ", start_pos);
            ParseArray(setting_view, start_pos, result.back());
            start_pos = setting_view.find_first_not_of("} ", start_pos);
        } else {
            // парсим простое значение
            // после выполнения start_pos - указывает на первый символ не равный пробелу
            result.back().addValue(std::make_shared<SettingsData>(ParseValue(setting_view, start_pos)));
        }
    }

    return result;
}

std::queue<std::string> snake::spliteLinesIntoName(const std::string &line) {
    std::queue<std::string> result;
    std::string name;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '.') {
            result.push(name);
            name.clear();
        } else {
            name += line[i];
        }
    }
    if (!name.empty()) {
        result.push(name);
    }
    return result;
}

std::vector<std::string> snake::findValue(const std::string &name_of_setting, const snake::ConfigReader &config)
{
    std::queue<std::string> names(std::move(spliteLinesIntoName(name_of_setting)));
    std::vector<std::string> result;

    auto find_SettingsData = config.find(names.front());
    names.pop();

    while (!names.empty() && find_SettingsData.get() != nullptr) {
        find_SettingsData = config.find(names.front(), find_SettingsData);
        names.pop();
    }

    if (find_SettingsData.get() != nullptr) {
        for (auto& value : find_SettingsData->_value) {
            result.push_back(value->_name_var);
        }
    } 

    return result;
}

snake::SettingsData::SettingsData(std::string name)
    : _name_var(name) {
}

void snake::SettingsData::addValue(std::shared_ptr<SettingsData> value) {
    _value.push_back(value);
}

snake::ConfigReader::ConfigReader(const std::string& file_name)
    : _file(std::move(file_name))
    , _settings(ParseSetting(_file)) {
    if (!_file.is_open()) {
        std::cerr << "Fatal error: file is could't be opened" << std::endl;
    }
}

snake::ConfigReader::~ConfigReader() {
    _file.close();
}

std::vector<snake::SettingsData>& snake::ConfigReader::getAllSettings() {
    return _settings;
}

std::shared_ptr<snake::SettingsData> snake::ConfigReader::find(const std::string& value, const std::shared_ptr<SettingsData> start_find) const {
    if (start_find.get() != nullptr) {
        auto it = std::find_if(start_find->_value.begin(), start_find->_value.end(), [&value](const std::shared_ptr<SettingsData> SettingsData) {
            return SettingsData->_name_var == value;
        });
        return (it == start_find->_value.end() ? nullptr : *it);
    }
    auto it = std::find_if(_settings.begin(), _settings.end(), [&value](const SettingsData& SettingsData) {
        return SettingsData._name_var == value;
    });
    return (it == _settings.end() ? nullptr : std::make_shared<SettingsData>(*it));
}

constexpr float DEFAULT_FLOAT_VALUE = 0.5f;
constexpr float DEFAULT_INT_VALUE = 0;

sf::Vector2f snake::findVector2f(const std::string &name_of_setting, const ConfigReader &config) {
    // ищем значение
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    if (find_value.size() != 2) {
        return {DEFAULT_FLOAT_VALUE, DEFAULT_FLOAT_VALUE};
    }
    return {std::stof(find_value[0]), std::stof(find_value[1])};
}

sf::Vector2i snake::findVector2i(const std::string &name_of_setting, const ConfigReader &config) {
    // ищем значение
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    if (find_value.size() != 2) {
        return {};
    }
    return {std::stoi(find_value[0]), std::stoi(find_value[1])};
}

sf::Vector2u snake::findVector2u(const std::string &name_of_setting, const ConfigReader &config) {
    sf::Vector2i int_value = findVector2i(name_of_setting, config);
    return {static_cast<unsigned int>(int_value.x), static_cast<unsigned int>(int_value.y)};
}

float snake::findFloat(const std::string &name_of_setting, const ConfigReader &config) {
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    if (find_value.size() != 1) {
        return DEFAULT_FLOAT_VALUE;
    }
    return std::stof(find_value[0]);
}

int snake::findInt(const std::string &name_of_setting, const ConfigReader &config) {
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    if (find_value.size() != 1) {
        return DEFAULT_INT_VALUE;
    }
    return std::stoi(find_value[0]);
}

std::string snake::findString(const std::string &name_of_setting, const ConfigReader &config) {
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    return find_value.front();
}
