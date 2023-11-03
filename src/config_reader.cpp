#include "config_reader.h"
#include <algorithm>
#include <cmath>
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

std::string snake::combineSettingsIntoOneLine(std::fstream &file) {
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

std::vector<snake::SettingsData> snake::ParseSetting(const std::string& file_name) {
    std::fstream file(file_name);\
    if (!file.is_open()) {
        std::cerr << "Fatal error: file is could't be opened" << std::endl;
    }
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
    file.close();
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

std::vector<std::string> snake::findValue(const std::string& name_of_setting, const snake::ConfigReader& config) {
    std::queue<std::string> names(std::move(spliteLinesIntoName(name_of_setting)));
    std::vector<std::string> result;

    auto find_SettingsData = const_cast<ConfigReader&>(config).find(names.front());
    names.pop();

    while (!names.empty() && find_SettingsData.get() != nullptr) {
        find_SettingsData = const_cast<ConfigReader&>(config).find(names.front(), find_SettingsData);
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
    : _file_name(file_name)
    , _settings(ParseSetting(_file_name)) {
}

void snake::ConfigReader::reload() {
    _settings = std::move(ParseSetting(_file_name));
}

const std::vector<snake::SettingsData>& snake::ConfigReader::getAllSettings() const {
    return _settings;
}

std::string snake::ConfigReader::getFileName() {
    return _file_name;
}

std::shared_ptr<snake::SettingsData> snake::ConfigReader::find(const std::string& value, const std::shared_ptr<SettingsData> start_find) {
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

// позаимствовал у сообщества
// https://riptutorial.com/cplusplus/example/4190/conversion-to-std--wstring
#include <codecvt>
#include <locale>

std::vector<std::wstring> snake::findArrWstring(const std::string &name_of_setting, const ConfigReader &config) {
    std::vector<std::string> find_value = findValue(name_of_setting, config);
    std::vector<std::wstring> result;
    result.reserve(find_value.size());
    for (size_t i = 0; i < find_value.size(); ++i) {
        std::wstring w_str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(find_value[i]);
        result.push_back(w_str);
    }
    return result;
}

std::string snake::makeTextFromConfig(const ConfigReader& config_ref) {
    const std::vector<snake::SettingsData>& settings_cref = config_ref.getAllSettings();
    std::string result;
    for (const SettingsData& val : settings_cref) {
        result += settingToString(val);
    }
    return result;
}

std::string snake::settingToString(const SettingsData &setting_val) {
    // Переписываем название и ставим знак =
    std::string str_result = setting_val._name_var;
    str_result += " = ";
    // Является ли переменная массивом
    if (setting_val._value.size() > 1 || !setting_val._value.front()->_value.empty()) {
        str_result += "{ ";
        // Является ли переменная вложенным массивом
        if (!setting_val._value.front()->_value.empty()) {
            bool is_frist = true;
            for (std::shared_ptr<snake::SettingsData> val : setting_val._value) {
                if (is_frist) {
                    str_result += "\n      ";
                    is_frist = false;
                } else {
                    str_result += "    , ";
                }
                str_result += settingToString(*val);
            }
        } else {
            bool is_first = true;
            for (std::shared_ptr<snake::SettingsData> val : setting_val._value) {
                if (!is_first) {
                    str_result += ", ";
                }
                str_result += val->_name_var;
                is_first = false;
            }
        }
        str_result += " }\n";
    } else {
        str_result += setting_val._value.front()->_name_var;
        str_result += "\n";
    }
    return str_result;
}

snake::SettingChanger::SettingChanger(ConfigReader &config)
    :_config_ref(config) {
}

snake::SettingChanger::~SettingChanger() {
    if (!hasChangedSettings()) {
        return;
    }
    if (_changed_setting.find("WINDOW_WIDSCREEN_DEFAULT") != _changed_setting.end() || _changed_setting.find("MAP_SIZE") != _changed_setting.end()) {
        reScaleGameObj();    // скелинг игровых объектов
        reSizeBackGround();  // скелинг фона главного меню
        // to do reScaleButton
    }

    // открываем поток для записи новых значений настроек
    std::ofstream _file_out(_config_ref.getFileName());
    std::string config_text(std::move(makeTextFromConfig(_config_ref)));
    _file_out << config_text;
    // закрываем поток записи
    _file_out.close();
}

bool snake::SettingChanger::hasChangedSettings() const {
    return !_changed_setting.empty();
}

void snake::SettingChanger::changeValue(const std::string &name_of_setting, const std::vector<std::string> &new_value) {
    // Разбиваем запрос
    std::queue<std::string> names(std::move(spliteLinesIntoName(name_of_setting)));

    // Находим значения настроек
    auto find_SettingsData = _config_ref.find(names.front());
    names.pop();

    while (!names.empty() && find_SettingsData.get() != nullptr) {
        find_SettingsData = _config_ref.find(names.front(), find_SettingsData);
        names.pop();
    }
    
    // Проверяем что нужная настройка найдена и размер передаваемых данных равен размеру найденных настроек
    if (find_SettingsData.get() != nullptr && new_value.size() == find_SettingsData->_value.size()) {
        for (size_t value_i = 0; value_i < find_SettingsData->_value.size(); ++value_i) {
            find_SettingsData->_value[value_i]->_name_var = new_value[value_i];
        }
        // если настройка была найдена, то записываем её в _changed_setting
        _changed_setting.insert(name_of_setting);
    }
}

void snake::SettingChanger::reScaleGameObj() {
    // данные для расчетов
    sf::Vector2u window_widscreen = findVector2u("WINDOWS_WIDSCREEN." + findString("WINDOW_WIDSCREEN_DEFAULT", _config_ref), _config_ref);
    sf::Vector2u map_size = findVector2u("MAP_SIZE", _config_ref);
    
    sf::Vector2u snake_tile_size = findVector2u("SNAKE_TILE_SIZE", _config_ref);
    sf::Vector2u eat_tile_size = findVector2u("EAT_TILE_SIZE", _config_ref);
    sf::Vector2u map_tile_size = findVector2u("MAP_TILE_SIZE", _config_ref);

    // По хитрой/загадочной формуле рассчитываем новое значение коэф. сжатия изображения
    sf::Vector2f snake_scale = calcNewScale(window_widscreen, map_size, snake_tile_size);
    sf::Vector2f map_scale = calcNewScale(window_widscreen, map_size, map_tile_size);
    sf::Vector2f eat_scale = calcNewScale(window_widscreen, map_size, eat_tile_size);

    // Перезаписываем конфиг
    changeValue("SNAKE_SCALE", {std::to_string(snake_scale.x), std::to_string(snake_scale.y)});
    changeValue("EAT_SCALE", {std::to_string(eat_scale.x), std::to_string(eat_scale.y)});
    changeValue("MAP_SCALE", {std::to_string(map_scale.x), std::to_string(map_scale.y)});
}

void snake::SettingChanger::reSizeBackGround() {
    // данные для расчетов
    sf::Vector2u window_widscreen = findVector2u("WINDOWS_WIDSCREEN." + findString("WINDOW_WIDSCREEN_DEFAULT", _config_ref), _config_ref);
    sf::Vector2f background_scale = findVector2f("BACKGROUND_SCALE", _config_ref);
    sf::Vector2u background_tile_size = findVector2u("BACKGROUND_TILE_SIZE", _config_ref);
    // считаем необходимое количество
    sf::Vector2f num_of_texture = {static_cast<float>(window_widscreen.x) / (static_cast<float>(background_tile_size.x) * background_scale.x), 
                                   static_cast<float>(window_widscreen.x) / (static_cast<float>(background_tile_size.x) * background_scale.x)};
    sf::Vector2u int_num_of_tex = {static_cast<unsigned int>(std::ceil(num_of_texture.x)), static_cast<unsigned int>(std::ceil(num_of_texture.y))};
    // Перезаписываем конфиг
    changeValue("BACKGROUND_SIZE", {std::to_string(int_num_of_tex.x), std::to_string(int_num_of_tex.y)});
}

sf::Vector2f snake::SettingChanger::calcNewScale(sf::Vector2u screen_size, sf::Vector2u map_size, sf::Vector2u tile_size) {
    return {static_cast<float>(screen_size.x) / (static_cast<float>(tile_size.x) * static_cast<float>(map_size.x))
    , static_cast<float>(screen_size.y) / (static_cast<float>(tile_size.y) * static_cast<float>(map_size.y))};
}
