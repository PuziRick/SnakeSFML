#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <set>
#include <SFML/Graphics.hpp>

// Правила для файла с настройками:
// 1. после названия переменной должен быть знак '=', а за ним следовать его значение
// 2. если переменная является массивом, то его элементы должны быть заключены в {} и
//    отделяться запятой
// 3. если переменная является строкой, то её значение должно быть заключено в ""
// 4. допускается использовать любое количество пробелов и переносов строки

namespace snake {

struct SettingsData {
    SettingsData(std::string name);
    void addValue(std::shared_ptr<SettingsData> value);  // добавить значение переменной
    std::string _name_var;                               // название переменной
    std::vector<std::shared_ptr<SettingsData>> _value;   // ссылки значения переменной
};

size_t findNameOfVaribale(std::string_view& str, size_t start_pos = 0);   // находит название переменной и возвращает позицию за ней не равную пробелу
size_t findStringValue(std::string_view& str, size_t start_pos = 0);      // находит значение строки и возвращает позицию за ней не равную пробелу
size_t findValue(std::string_view& str, size_t start_pos = 0);            // находит в str значение переменной и возвращает позицию за ней не равную пробелу

// Функции ParseName ... ParseArray модифицируют start_pos
SettingsData ParseName(std::string_view str, size_t& start_pos);                // выделяет имя переменной из строки
SettingsData ParseStringValue(std::string_view str, size_t& start_pos);         // выделяет значение строковой переменной из строки
SettingsData ParseValue(std::string_view str, size_t& start_pos);               // выделяет значение переменной из строки
void ParseArray(std::string_view str, size_t& start_pos, SettingsData& header); // выделяет массив значений из строки

std::string combineSettingsIntoOneLine(std::fstream& file); // объединить настройки из потока file в одну строку
std::vector<SettingsData> ParseSetting(const std::string& file); // разбивает входной поток file на вектор настроек

class ConfigReader {
public:
    explicit ConfigReader(const std::string& file_name);
    void reload();                                           // перезагрузить данные
    const std::vector<SettingsData>& getAllSettings() const; // возвращает все настройки
    std::string getFileName();                               // возвращает название файла
    std::shared_ptr<SettingsData> find(const std::string& value, const std::shared_ptr<SettingsData> start_find = nullptr);
private:
    std::string _file_name;
    std::vector<SettingsData> _settings;
};

std::queue<std::string> spliteLinesIntoName(const std::string& line);     // разделяет поисковой запрос на очередь запросов

// функция для поиска нужной настройки (вернет empty если значение не найдено)
// синтаксис для поиска вложенного массива "NAME_ARR.NAME_NESTED_ARR"
std::vector<std::string> findValue(const std::string& name_of_setting, const ConfigReader& config);

// Вспомогательные функции, конвертирующие найденные настройки в нужный формат
sf::Vector2f findVector2f(const std::string& name_of_setting, const ConfigReader& config);
sf::Vector2i findVector2i(const std::string& name_of_setting, const ConfigReader& config);
sf::Vector2u findVector2u(const std::string& name_of_setting, const ConfigReader& config);
float findFloat(const std::string& name_of_setting, const ConfigReader& config);
int findInt(const std::string& name_of_setting, const ConfigReader& config);
std::string findString(const std::string& name_of_setting, const ConfigReader& config);

// Функции переводящие данные из config в строку
std::string makeTextFromConfig(const ConfigReader& config_ref);
std::string settingToString(const SettingsData& setting_val);

// класс для внесения изменений в настройки, RAII - диструктор вносит изменения в config файл
class SettingChanger {
public:
    SettingChanger(ConfigReader& config);
    ~SettingChanger();
    bool hasChangedSettings() const;       // возвращает true если настройки были изменены
    void changeValue(const std::string& name_of_setting, const std::vector<std::string>& new_value);
private:
    ConfigReader& _config_ref;
    std::set<std::string> _changed_setting; // все настройки, которые были изменены
};

} // конец namespace snake

