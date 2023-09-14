#include "config_reader.h"
#include <iostream>
#include <algorithm>

size_t snake::findNameOfVaribale(std::string_view& str, size_t start_pos) {
    size_t pos_first = str.find_first_not_of(' ', start_pos);                                      // первый символ названия переменной
    size_t pos_equal = str.find_first_of('=', pos_first);                                          // первый знак =
    size_t pos_last = str[pos_equal - 1] == ' ' ? str.find_first_of(' ', pos_first) : (pos_equal); // последний знак имени переменной
    
    if (pos_first == std::string_view::npos || pos_first < start_pos) {
        return std::string_view::npos;
    }

    str.remove_prefix(pos_first);
    str.remove_suffix(str.size() - pos_last + pos_first);

    return ++pos_last;
}

size_t snake::findStringValue(std::string_view& str, size_t start_pos) {
    size_t pos_first = str.find_first_of('\"',start_pos) + 1;        // находим первую и последнюю ковычку 

    if (pos_first == std::string_view::npos || pos_first < start_pos) {
        return std::string_view::npos;
    }

    size_t pos_last = str.find_first_of('\"', pos_first);

    str.remove_prefix(pos_first);
    str.remove_suffix(str.size() - pos_last + pos_first);

    return ++pos_last;
}

std::string snake::combineSettingsIntoOneLine(std::ifstream &file)
{
    std::string settings;
    std::string line;
    while (std::getline(file, line)) {
        settings += line;
    }
    return settings;
}

std::vector<snake::Data> snake::ParseSetting(std::ifstream& file) {
    std::string settings(std::move(combineSettingsIntoOneLine(file)));
    std::string_view setting_view(settings);
    
    size_t start_pos = 0;

    while (start_pos != std::string_view::npos) {
        // создаем копию string_view
        std::string_view tmp(setting_view);
        // сначала записываем имя переменной
        start_pos = findNameOfVaribale(tmp, start_pos); // позиция после символа =
        std::cout << "name_var = \"" << tmp << "\"" << std::endl;

        tmp = setting_view;
        if (tmp[tmp.find_first_not_of(' ',start_pos)] == '\"') {
            start_pos = findStringValue(tmp, start_pos);
            std::cout << " string(\"" << tmp << "\")" << std::endl;
        }

        tmp = setting_view;
        if (tmp[tmp.find_first_not_of(' ',start_pos)] == '{') {
            start_pos = tmp.find_first_of('}');
        }
    }

    return std::vector<snake::Data>();
}

snake::Data::Data(std::string& name)
    : _name_var(name) {
}

void snake::Data::addValue(std::shared_ptr<Data> value) {
    _value.push_back(value);
}

snake::ConfigReader::ConfigReader(const std::string& file_name)
    : _file(std::move(file_name)) {
    if (!_file.is_open()) {
        std::cerr << "Fatal error: file is could't be opened" << std::endl;
    }
}

std::ifstream &snake::ConfigReader::getFile() {
    return _file;
}

/*
std::vector<snake::Data> snake::ConfigReader::getAllSettings() {
    return _settings;
}

std::vector<std::shared_ptr<snake::Data>>& snake::ConfigReader::findSetting(std::string& name_of_setting) {
    auto it = std::find_if(_settings.begin(), _settings.end(), [&name_of_setting](Data& data) {
        return data._name_var == name_of_setting;
    });
    return it->_value;
}
*/