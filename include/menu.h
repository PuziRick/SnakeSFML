#pragma once

#include <vector>

#include "button.h"
#include "map.h"
#include "draw.h"
#include "config_reader.h"

namespace snake {

std::vector<Button> creatDefaultButtons();

class Menu {
public:
    Menu(sf::RenderWindow& window, ConfigReader& config);
private:
    std::vector<Button> _buttons;      // перечислены все кнопки
    Map _background;                   // удобно использовать класс Map для составления случайного заднего фона
    std::vector<DrawButton> _draw_b;
    DrawMap _background;
};

} // конец namespace snake