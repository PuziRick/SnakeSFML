#include <SFML/Graphics.hpp>

#include "settings.h"
#include "engine.h"
#include "config_reader.h"

#include <memory>
#include <iostream>
#include <sstream>

int main() {
    snake::ConfigReader config_file("../tested_config.txt");
    auto arr = snake::ParseSetting(config_file.getFile());

    for (snake::Data setting : arr) {
        std::cout << setting._name_var << " :";
        for (auto s : setting._value) {
            std::cout << " " << s->_name_var;
        }
        std::cout << std::endl;
    }
}