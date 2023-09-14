#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
// Правила для файла с настройками:
// 1. после названия переменной должен быть знак '=', а за ним следовать его значение
// 2. если переменная является массивом, то его элементы должны быть заключены в {} и
//    отделяться запятой
// 3. если переменная является строкой, то её значение должно быть заключено в ""
// 4. допускается использовать любое количество пробелов и переносов строки

namespace snake {

struct Data {
    Data(std::string& name);
    void addValue(std::shared_ptr<Data> value);  // добавить значение переменной
    std::string _name_var;                       // название переменной
    std::vector<std::shared_ptr<Data>> _value;   // ссылки значения переменной
};

size_t findNameOfVaribale(std::string_view& str, size_t start_pos = 0); // находит название переменной
size_t findStringValue(std::string_view& str, size_t start_pos = 0);    // находит значение строки

Data ParseDataIntoString(std::string& line);
std::string combineSettingsIntoOneLine(std::ifstream& file); // объединить настройки из потока file в одну строку
std::vector<Data> ParseSetting(std::ifstream& file);         // разбивает входной поток file на вектор настроек

class ConfigReader {
public:
    explicit ConfigReader(const std::string& file_name);
    std::ifstream& getFile();
    //std::vector<Data> getAllSettings();                                            // возвращает все настройки
    //std::vector<std::shared_ptr<Data>>& findSetting(std::string& name_of_setting); // возрващает значение для указанной переменной
private:
    std::ifstream _file;
    //std::vector<Data> _settings;
};

} // конец namespace snake

