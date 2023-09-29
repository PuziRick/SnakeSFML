#pragma once

#include <SFML/Graphics.hpp>
#include "config_reader.h"

namespace snake {

// Основной класс игры
class Game {
public:
    Game(const std::string& config_name);
private:
    ConfigReader _config;
};

}

