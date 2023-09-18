#pragma once
#include <fstream>
#include "my_test_framework.h"
#include "config_reader.h"
#include <memory>
#include <random>

void TestValueReader() {
    std::ifstream _file("tested_configs/config_value.txt");
    ASSERT_HINT(_file.is_open(), "Couldn't open the test config file");

    // Парсим тестовый конфиг файл
    std::vector<snake::Data> arr = snake::ParseSetting(_file);

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

    for (snake::Data& data : arr) {
        ASSERT_EQUAL_HINT(data._name_var, CORRECT_ARR[pos_correct_arr].first, "Incorrect reading of the variable name");
        for (std::shared_ptr<snake::Data> value : data._value) {
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
    std::vector<snake::Data> arr = snake::ParseSetting(_file);

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
    _file.close();
}

void TestCombinedData() {
    std::ifstream _file("tested_configs/config_combine.txt");
    ASSERT_HINT(_file.is_open(), "Сouldn't open the test config file");
    // Парсим тестовый конфиг файл
    std::vector<snake::Data> arr = snake::ParseSetting(_file);
    
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
}

// to do добавить проверку на большом файле настроек

void TestConfigReader() {
    RUN_TEST_TAB(TestValueReader, 1);  // проверяем чтение переменных
    RUN_TEST_TAB(TestStringReader, 1); // проверяем чтение строковых переменных
    RUN_TEST_TAB(TestCombinedData, 1); // проверяем чтение всех видов переменных
}