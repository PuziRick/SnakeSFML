#include <SFML/Graphics.hpp>

#include "settings.h"
#include "engine.h"
#include "config_reader.h"

#include <memory>
#include <iostream>

using namespace std;
using std::literals::string_literals::operator""s;

int main() {
    snake::ConfigReader config_file("../config.txt");
    //std::string settings = snake::combineSettingsIntoOneLine(config_file.getFile());

    snake::ParseSetting(config_file.getFile()); 
}