#include "menu.h"
#include "settings.h"
#include <iostream>

std::vector<snake::Button> snake::creatDefaultButtons() {
    std::vector<Button> buttons = {
        Button(L"start") ,
        Button(L"setting") ,
        Button(L"quit")
    };
    return buttons;
}

std::vector<snake::DrawButton> snake::creatDrawButton(sf::RenderWindow &window, TileSet &tiles, std::vector<Button>& buttons, ConfigReader &config) {
    std::map<snake::BUTTON_STATES, sf::Vector2u> button_pos = snake::settings::loadButtonSettings(config)._pos_to_tiles;
    std::vector<DrawButton> result;
    result.reserve(buttons.size());

    for (size_t i = 0; i < buttons.size(); ++i) {
        DrawButton draw_b(window, tiles, buttons[i], button_pos);
        result.push_back(draw_b);
    }

    return result;
}

snake::DrawMap snake::creatDrawBackground(sf::RenderWindow &window, snake::TileSet &tile_set, const snake::Map& background, const ConfigReader &config) {
    snake::settings::MapSettings back_conf = snake::settings::loadMapSettings(config, "BACKGROUND");
    return {window, tile_set, background, back_conf._pos_to_tiles};
}

snake::Menu::Menu(sf::RenderWindow& window, ConfigReader &config)
    : _buttons(std::move(creatDefaultButtons()))
    , _tile_set_button(snake::settings::creatTileSet(snake::settings::loadButtonSettings(config)._tiles))
    , _draw_buttons(creatDrawButton(window, _tile_set_button, _buttons, config))
    , _background(std::move(snake::settings::creatMap(config, "BACKGROUND"))) 
    , _tile_set_background(snake::settings::creatTileSet(snake::settings::loadMapSettings(config, "BACKGROUND")._tiles))
    , _draw_back(creatDrawBackground(window, _tile_set_background, _background, config)) {
    // устанавливаем все кнопки на свои места
    setButtonsToPossition();
}

void snake::Menu::update([[maybe_unused]]float time) {
    _draw_back.Draw();
    for (DrawButton& draw_button : _draw_buttons) {
        draw_button.Draw();
    }
}

void snake::Menu::setButtonsToPossition() {
    for (size_t i = 0; i < _draw_buttons.size(); ++i) {
        _draw_buttons[i].placeButtonVertically(snake::LineSegmentInfo(static_cast<int>(i + 1)));
    }
}
