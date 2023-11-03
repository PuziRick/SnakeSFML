#pragma once

#include <vector>

#include "button.h"
#include "map.h"
#include "draw.h"
#include "config_reader.h"
#include "settings.h"

namespace snake {

std::vector<Button> creatButtons(ConfigReader& config, sf::Font& font);
std::vector<DrawButton> creatDrawButton(sf::RenderWindow& window, TileSet& tiles, std::vector<Button>& buttons, ConfigReader& config);
sf::Font creatFont(const ConfigReader& config);
DrawMap creatDrawBackground(sf::RenderWindow& window, snake::TileSet& tile_set, const snake::Map& background, const ConfigReader& config);

class Menu {
public:
    Menu(sf::RenderWindow& window, ConfigReader& config);
    settings::GAME_STATE update([[maybe_unused]] float time, sf::Event& event);
private:
    sf::RenderWindow& _window_ref;         // ссылка на окно
    sf::Font _font;                        // шрифт для текста на кнопках
    std::vector<Button> _buttons;          // перечислены все кнопки
    TileSet _tile_set_button;              // тайлсет кнопки
    std::vector<DrawButton> _draw_buttons; // отрисовщики кнопок
    Map _background;                       // удобно использовать класс Map для составления случайного заднего фона
    TileSet _tile_set_background;          // тайлсет фона
    DrawMap _draw_back;                    // отрисовщик фона
    sf::Vector2i _mouse_pos;               // позиция курсора
private:
    void setButtonsToPossition();          // устанавливает позицую кнопок
    void proccesSelect();                  // обрабатывает наведение мышки
    bool isCursorOverButton(const Button& button) const; // проверка что курсор находится над кнопкой
    settings::GAME_STATE click(Button& button, sf::Event& event, settings::GAME_STATE& game_state); // обработка нажатия кнопки
    settings::GAME_STATE chooseAction(Button& button);
};

/*
class SettingMenu {
public:
    SettingMenu(sf::RenderWindow& window, ConfigReader& config);
private:
    sf::RenderWindow& _window_ref;         // ссылка на окно
    sf::Font _font;                        // шрифт для текста на кнопках
};
*/
} // конец namespace snake