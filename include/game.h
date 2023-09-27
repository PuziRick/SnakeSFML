#pragma once

#include <SFML/Graphics.hpp>
#include "engine.h"
#include "config_reader.h"

namespace snake {

// Основной класс игры, работает по принципу RAII
class Game {
public:
    Game(const std::string& config_name);
private:
    ConfigReader _config;
};

}

