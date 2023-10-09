#pragma once

#include <fstream>
#include "my_test_framework.h"
#include "config_reader.h"
#include <memory>
#include <random>
#include <map>

void TestValueReader() {
    std::string _file_name("tested_configs/config_value.txt");

    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file_name);

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
}

void TestStringReader() {
    std::string _file_name("tested_configs/config_string.txt");

    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file_name);

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
}

void TestCombinedSettingsData() {
    std::string _file_name("tested_configs/config_combine.txt");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file_name);
    
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
}

struct Array_SettingsData {
    std::string name;
    std::pair<std::string, std::string> value;
};

void Test1DArray() {
    std::string _file_name("tested_configs/config_array.txt");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file_name);

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
}

void Test2DArray() {
    std::string _file_name("tested_configs/config_array_2d.txt");
    // Парсим тестовый конфиг файл
    std::vector<snake::SettingsData> arr = snake::ParseSetting(_file_name);
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

void TestChangeData() {
    std::string file_name = "tested_configs/config_change_data.txt";
    snake::ConfigReader config_reader(file_name);
    // все возможные запросы и ожидаемые ответы
    const std::map<std::string, std::vector<std::string>> REQUESTS_ANSWER = {
        {"ARRAY" , {"960", "640"}} ,
        {"STRING" , {"string1 and string2"}} ,
        {"VALUE" , {"1"}} ,
        {"2D_ARRAY", {"FIRST_ARR", "SECOND_ARR", "THIRD_ARR"}} ,
        {"2D_ARRAY.FIRST_ARR", {"2", "3"}} ,
        {"2D_ARRAY.SECOND_ARR", {"4", "5"}} ,
        {"2D_ARRAY.THIRD_ARR", {"6", "7"}}
    };
    const std::map<std::string, std::vector<std::string>> CHANGED_REQUESTS_ANSWER = {
        {"ARRAY" , {"1080", "900"}} ,
        {"STRING" , {"new string"}} ,
        {"VALUE" , {"10"}} ,
        {"2D_ARRAY", {"FIRST_ARR", "SECOND_ARR", "THIRD_ARR"}} ,
        {"2D_ARRAY.FIRST_ARR", {"20", "30"}} ,
        {"2D_ARRAY.SECOND_ARR", {"40", "50"}} ,
        {"2D_ARRAY.THIRD_ARR", {"60", "70"}}
    };
    // проверяем значения без изменения
    for (const auto& [name, value] : REQUESTS_ANSWER) {
        std::vector<std::string> answer = snake::findValue(name, config_reader);
        ASSERT_EQUAL_HINT(answer.size(), value.size(), "Incorrect size of found values");
        for (size_t i = 0; i < answer.size(); ++i) {
            ASSERT_EQUAL_HINT(answer[i], value[i], "Incorrect value found");
        }
    }
    // меняем данные, т.к. snake::SettingChanger сделан по идиоме RAII, ограничиваем его область видимости {}
    {
        snake::SettingChanger changer(config_reader);
        changer.changeValue("ARRAY", {"1080", "900"});
        changer.changeValue("STRING", {"\"new string\""});
        changer.changeValue("VALUE", {"10"});
        changer.changeValue("2D_ARRAY.FIRST_ARR", {"20","30"});
        changer.changeValue("2D_ARRAY.SECOND_ARR", {"40","50"});
        changer.changeValue("2D_ARRAY.THIRD_ARR", {"60","70"});
        // проверяем значения
        for (const auto& [name, value] : CHANGED_REQUESTS_ANSWER) {
            std::vector<std::string> answer = snake::findValue(name, config_reader);
            ASSERT_EQUAL_HINT(answer.size(), value.size(), "Incorrect size of found values");
            for (size_t i = 0; i < answer.size(); ++i) {
                if (answer[i] != "\"new string\"" ) {
                    ASSERT_EQUAL_HINT(answer[i], value[i], "Incorrect value found");
                }
            }
        }
    }
    // в конце проверям что данные перезаписались в config файл
    config_reader.reload();
    for (const auto& [name, value] : REQUESTS_ANSWER) {
        std::vector<std::string> answer = snake::findValue(name, config_reader);
        for (size_t i = 0; i < answer.size(); ++i) {
            if (answer[i] != "FIRST_ARR" && answer[i] != "SECOND_ARR" && answer[i] != "THIRD_ARR" ) {
                ASSERT_HINT(answer[i] != value[i], "Incorrect value found");
            }
        }
    }
}

void TestConfigReader() {
    RUN_TEST_TAB(TestValueReader, 1);  // проверяем чтение переменных
    RUN_TEST_TAB(TestStringReader, 1); // проверяем чтение строковых переменных
    RUN_TEST_TAB(Test1DArray, 1);      // проверяем простой одномерный массив
    RUN_TEST_TAB(Test2DArray, 1);      // проверяем чтение двумерного массива
    RUN_TEST_TAB(TestCombinedSettingsData, 1); // проверяем чтение всех видов переменных
    RUN_TEST_TAB(TestConfigFind, 1);   // проверяем поиск значения настройки
    RUN_TEST_TAB(TestChangeData, 1);   // проверяем запись данных
}