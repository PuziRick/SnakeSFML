#pragma once

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "config_reader.h"

namespace snake {

enum class GAME_STATE {
    MENU, GAME, SETTING
};

// Основной класс игры, работает по принципу RAII
class Game {
public:
    Game(const std::string& config_name);
private:
    ConfigReader _config;
};

}

