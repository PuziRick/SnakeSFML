#pragma once

#include <vector>

#include "button.h"
#include "map.h"
#include "draw.h"
#include "config_reader.h"

namespace snake {

std::vector<Button> creatDefaultButtons();
std::vector<DrawButton> creatDrawButton(sf::RenderWindow& window, TileSet& tiles, std::vector<Button>& buttons, ConfigReader& config);
DrawMap creatDrawBackground(sf::RenderWindow& window, snake::TileSet& tile_set, const snake::Map& background, const ConfigReader& config);

class Menu {
public:
    Menu(sf::RenderWindow& window, ConfigReader& config);
    void update( [[maybe_unused]] float time);
private:
    std::vector<Button> _buttons;          // перечислены все кнопки
    TileSet _tile_set_button;              // тайлсет кнопки
    std::vector<DrawButton> _draw_buttons; // отрисовщики кнопок
    Map _background;                       // удобно использовать класс Map для составления случайного заднего фона
    TileSet _tile_set_background;          // тайлсет фона
    DrawMap _draw_back;                    // отрисовщик фона
private:
    void setButtonsToPossition();
};

} // конец namespace snake