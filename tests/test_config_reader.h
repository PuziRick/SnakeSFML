#pragma once

#include <fstream>
#include "my_test_framework.h"
#include "config_reader.h"
#include <memory>
#include <random>
#include <map>

void TestValueReader() {
    std::ifstream _file("tested_configs/config_value.txt");
    ASSERT_HINT(_file.is_open(), "Couldn't open the test config file");

    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file);

    // Колхоз и мне очень стыдно
    const std::vector<std::pair<std::string, std::string>> CORRECT_ARR = {
        {"NORMAL_FORMAT", "1"} ,
        {"EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_LINE", "2"} ,
        {"EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "3"} ,
        {"EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "4"} ,
        {"EXTRA_SPACE_AT_THE_END_OF_THE_LINE", "5"} ,
        {"EXTRA_SPACE", "6"} ,
        {"WITHOUT_SPACE", "7"} ,
        {"WITH_LINE_BREAK", "8"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_FIRST_LINE", "9"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "10"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "11"}
    };
    // пробегаем по полученным данным и сравниваем их с эталонами
    size_t pos_correct_arr = 0;

    for (snake::SettingsData& SettingsData : arr) {
        ASSERT_EQUAL_HINT(SettingsData._name_var, CORRECT_ARR[pos_correct_arr].first, "Incorrect reading of the variable name");
        for (std::shared_ptr<snake::SettingsData> value : SettingsData._value) {
            ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR[pos_correct_arr].second, "Incorrect reading of the variable value");
        }
        ++pos_correct_arr;
    }

    _file.close();
}

void TestStringReader() {
    std::ifstream _file("tested_configs/config_string.txt");
    ASSERT_HINT(_file.is_open(), "Сouldn't open the test config file");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file);

    const std::vector<std::pair<std::string, std::string>> CORRECT_ARR = {
        {"NORMAL_FORMAT", "string 1"} ,
        {"EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_LINE", "string 2"} ,
        {"EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "string 3"} ,
        {"EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "string 4"} ,
        {"EXTRA_SPACE_AT_THE_END_OF_THE_LINE", "string 5"} ,
        {"EXTRA_SPACE", "string 6"} ,
        {"WITHOUT_SPACE", "string 7"} ,
        {"WITH_LINE_BREAK", "string 8"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_FIRST_LINE", "string 9"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "string 10"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "string 11"} ,
        {"SAVE_SPACE_IN_STRING_VALUE_1", "       string 12"} ,
        {"SAVE_SPACE_IN_STRING_VALUE_2", "string        13"} ,
        {"SAVE_SPACE_IN_STRING_VALUE_3", "string 14       "}
    };
    // пробегаем по полученным данным и сравниваем их с эталонами
    size_t pos_correct_arr = 0;

    for (snake::SettingsData& SettingsData : arr) {
        ASSERT_EQUAL_HINT(SettingsData._name_var, CORRECT_ARR[pos_correct_arr].first, "Incorrect reading of the variable name");
        for (std::shared_ptr<snake::SettingsData> value : SettingsData._value) {
            ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR[pos_correct_arr].second, "Incorrect reading of the variable value");
        }
        ++pos_correct_arr;
    }

    _file.close();
}

void TestCombinedSettingsData() {
    std::ifstream _file("tested_configs/config_combine.txt");
    ASSERT_HINT(_file.is_open(), "Сouldn't open the test config file");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file);
    
    const std::vector<std::pair<std::string, std::string>> CORRECT_ARR = {
        {"NORMAL_FORMAT", "1"} ,
        {"EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_LINE", "2"} ,
        {"EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "3"} ,
        {"EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "4"} ,
        {"EXTRA_SPACE_AT_THE_END_OF_THE_LINE", "5"} ,
        {"EXTRA_SPACE", "6"} ,
        {"WITHOUT_SPACE", "7"} ,
        {"WITH_LINE_BREAK", "8"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_FIRST_LINE", "9"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "10"} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "11"},
        {"STRING_NORMAL_FORMAT", "string 1"} ,
        {"STRING_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_LINE", "string 2"} ,
        {"STRING_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "string 3"} ,
        {"STRING_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "string 4"} ,
        {"STRING_EXTRA_SPACE_AT_THE_END_OF_THE_LINE", "string 5"} ,
        {"STRING_EXTRA_SPACE", "string 6"} ,
        {"STRING_WITHOUT_SPACE", "string 7"} ,
        {"STRING_WITH_LINE_BREAK", "string 8"} ,
        {"STRING_WITH_LINE_BREAK_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_FIRST_LINE", "string 9"} ,
        {"STRING_WITH_LINE_BREAK_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", "string 10"} ,
        {"STRING_WITH_LINE_BREAK_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", "string 11"} ,
        {"STRING_SAVE_SPACE_IN_STRING_VALUE_1", "       string 12"} ,
        {"STRING_SAVE_SPACE_IN_STRING_VALUE_2", "string        13"} ,
        {"STRING_SAVE_SPACE_IN_STRING_VALUE_3", "string 14       "}
    };
    // пробегаем по полученным данным и сравниваем их с эталонами
    size_t pos_correct_arr = 0;

    for (snake::SettingsData& SettingsData : arr) {
        ASSERT_EQUAL_HINT(SettingsData._name_var, CORRECT_ARR[pos_correct_arr].first, "Incorrect reading of the variable name");
        for (std::shared_ptr<snake::SettingsData> value : SettingsData._value) {
            ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR[pos_correct_arr].second, "Incorrect reading of the variable value");
        }
        ++pos_correct_arr;
    }

    _file.close();
}

struct Array_SettingsData {
    std::string name;
    std::pair<std::string, std::string> value;
};

void Test1DArray() {
    std::ifstream _file("tested_configs/config_array.txt");
    ASSERT_HINT(_file.is_open(), "Сouldn't open the test config file");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file);

    std::vector<Array_SettingsData> CORRECT_ARR = {
        {"NORMAL_FORMAT_1", {"1","2"}} ,
        {"NORMAL_FORMAT_2", {"1","2"}} ,
        {"EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_LINE", {"3","4"}} ,
        {"EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", {"5","6"}} ,
        {"EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", {"7","8"}} ,
        {"EXTRA_SPACE_AT_THE_END_OF_THE_LINE", {"9","10"}} ,
        {"EXTRA_SPACE", {"11 ","12 "}} ,    
        {"WITHOUT_SPACE", {"13","14"}} ,
        {"WITH_LINE_BREAK", {"15","16"}} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_IN_THE_BEGINNING_OF_THE_FIRST_LINE", {"17","18"}} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_BEFORE_THE_SIGN_EQUAL", {"19","20"}} ,
        {"WITH_LINE_BREAK_EXTRA_SPACE_AFTER_THE_SIGN_EQUAL", {"21","22"}}
    };
    // пробегаем по полученным данным и сравниваем их с эталонами
    size_t pos_correct_arr = 0;

    for (snake::SettingsData& SettingsData : arr) {
        ASSERT_EQUAL_HINT(SettingsData._name_var, CORRECT_ARR[pos_correct_arr].name, "Incorrect reading of the variable name");
        bool is_first = true; // mvp проверка 
        for (std::shared_ptr<snake::SettingsData> value : SettingsData._value) {
            if (is_first) {
                ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR[pos_correct_arr].value.first, "Incorrect reading of the variable value");
                is_first = false;
            } else {
                ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR[pos_correct_arr].value.second, "Incorrect reading of the variable value");
            }
        }
        ++pos_correct_arr;
    }

    _file.close();
}

void Test2DArray() {
    std::ifstream _file("tested_configs/config_array_2d.txt");
    ASSERT_HINT(_file.is_open(), "Сouldn't open the test config file");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file);
    std::pair<std::string, std::vector<Array_SettingsData>> CORRECT_ARR = {
        "SNAKE_POS_TILES", {
            {"HEAD_UP",  {"0","0"}} , 
            {"HEAD_DOWN", {"2","0"}} , 
            {"HEAD_LEFT", {"3","0"}} , 
            {"HEAD_RIGHT", {"1","0"}} , 
            {"TAIL_UP", {"0","1"}} , 
            {"TAIL_DOWN", {"2","1"}} , 
            {"TAIL_LEFT", {"3","1"}} , 
            {"TAIL_RIGHT", {"1","1"}} , 
            {"HORIZONTAL_BODY", {"1","3"}} , 
            {"VERTICAL_BODY", {"0","3"}} , 
            {"RUSSIAN_G_LETTER_BODY", {"1","2"}} , 
            {"INVERSE_RUSSIAN_G_LETTER_BODY", {"2","2"}} , 
            {"L_BODY", {"0","2"}} , 
            {"INVERSE_L_BODY", {"3","2"}}
        }
    };

    // пробегаем по полученным данным и сравниваем их с эталонами
    size_t pos_correct_arr = 0;

    for (snake::SettingsData& SettingsData : arr) {
        ASSERT_EQUAL_HINT(SettingsData._name_var, CORRECT_ARR.first, "Incorrect reading of the variable name");
        for (std::shared_ptr<snake::SettingsData> value_name : SettingsData._value) {
            ASSERT_EQUAL_HINT(value_name->_name_var, CORRECT_ARR.second[pos_correct_arr].name, "Incorrect reading of the variable value (name)");
            bool is_first = true; // mvp проверка 
            for (std::shared_ptr<snake::SettingsData> value : value_name->_value) {
                if (is_first) {
                    ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR.second[pos_correct_arr].value.first, "Incorrect reading of the variable value");
                    is_first = false;
                } else {
                    ASSERT_EQUAL_HINT(value->_name_var, CORRECT_ARR.second[pos_correct_arr].value.second, "Incorrect reading of the variable value");
                }
            }
            ++pos_correct_arr;
        }
    }
}

void TestConfigFind() {
    std::string file_name = "tested_configs/config_norm.txt";
    snake::ConfigReader config_reader(file_name);
    // все возможные запросы и ожидаемые ответы
    const std::map<std::string, std::vector<std::string>> REQUESTS_ANSWER = {
        {"WINDOWS_WIDSCREEN" , {"960", "640"}} ,
        {"WINDOWS_NAME" , {"snake"}} ,
        {"SNAKE_TILESET_NAME" , {"images/snake.png"}} ,
        {"SNAKE_TILE_SIZE" , {"64", "64"}} ,
        {"SNAKE_SCALE" , {"0.5"}} ,
        {"SNAKE_START_POSITION" , {"4","4"}} ,
        {"SNAKE_START_SIZE" , {"3"}} ,
        {"SNAKE_POS_TILES", {
            "HEAD_UP" ,
            "HEAD_DOWN" ,
            "HEAD_LEFT" ,
            "HEAD_RIGHT" ,
            "TAIL_UP" ,
            "TAIL_DOWN" ,
            "TAIL_LEFT" ,
            "TAIL_RIGHT" ,
            "HORIZONTAL_BODY" ,
            "VERTICAL_BODY" ,
            "RUSSIAN_G_LETTER_BODY" ,
            "INVERSE_RUSSIAN_G_LETTER_BODY" ,
            "L_BODY" ,
            "INVERSE_L_BODY"}
        } ,
        {"SNAKE_POS_TILES.HEAD_UP",  {"0","0"}} ,
        {"SNAKE_POS_TILES.HEAD_DOWN", {"2","0"}} ,
        {"SNAKE_POS_TILES.HEAD_LEFT", {"3","0"}} ,
        {"SNAKE_POS_TILES.HEAD_RIGHT", {"1","0"}} ,
        {"SNAKE_POS_TILES.TAIL_UP", {"0","1"}} ,
        {"SNAKE_POS_TILES.TAIL_DOWN", {"2","1"}} ,
        {"SNAKE_POS_TILES.TAIL_LEFT", {"3","1"}} ,
        {"SNAKE_POS_TILES.TAIL_RIGHT", {"1","1"}} ,
        {"SNAKE_POS_TILES.HORIZONTAL_BODY", {"1","3"}} ,
        {"SNAKE_POS_TILES.VERTICAL_BODY", {"0","3"}} ,
        {"SNAKE_POS_TILES.RUSSIAN_G_LETTER_BODY", {"1","2"}} ,
        {"SNAKE_POS_TILES.INVERSE_RUSSIAN_G_LETTER_BODY", {"2","2"}} ,
        {"SNAKE_POS_TILES.L_BODY", {"0","2"}} ,
        {"SNAKE_POS_TILES.INVERSE_L_BODY", {"3","2"}} ,
        {"MAP_TILESET_NAME" , {"images/grass.png"}} ,
        {"MAP_TILE_SIZE" , {"64","64"}} ,
        {"MAP_SCALE" , {"0.5"}} ,
        {"MAP_NUMBER_OF_TEXTURES" , {"3"}} ,
        {"MAP_SIZE" , {"30","20"}} ,
        {"EAT_IMAGE_NAME" , {"images/apple.png"}} ,
        {"EAT_POS_TILES" , {"0", "0"}} ,
        {"GAME_SPEED", {"NORMAL"}}
    };

    for (const auto& [name, value] : REQUESTS_ANSWER) {
        std::vector<std::string> answer = snake::findValue(name, config_reader);
        ASSERT_EQUAL_HINT(answer.size(), value.size(), "Incorrect size of found values");
        for (size_t i = 0; i < answer.size(); ++i) {
            ASSERT_EQUAL_HINT(answer[i], value[i], "Incorrect value found");
        }
    }

    const std::string REQUEST_TO_WHICH_THERE_IS_NO_RESPONSE = "WHAT_IS_THE_MEANING_OF_LIFE";
    std::vector<std::string> answer = snake::findValue(REQUEST_TO_WHICH_THERE_IS_NO_RESPONSE, config_reader);
    ASSERT_HINT(answer.empty(), "Incorrect found empty value");
}

// to do добавить проверку на большом файле настроек

void TestConfigReader() {
    RUN_TEST_TAB(TestValueReader, 1);  // проверяем чтение переменных
    RUN_TEST_TAB(TestStringReader, 1); // проверяем чтение строковых переменных
    RUN_TEST_TAB(Test1DArray, 1);      // проверяем простой одномерный массив
    RUN_TEST_TAB(Test2DArray, 1);      // проверяем чтение двумерного массива
    RUN_TEST_TAB(TestCombinedSettingsData, 1); // проверяем чтение всех видов переменных
    RUN_TEST_TAB(TestConfigFind, 1);   // проверяем поиск значения настройки
}