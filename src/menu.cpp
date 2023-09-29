#include "menu.h"
#include <iostream>

std::vector<snake::Button> snake::creatDefaultButtons(sf::Font& font) {
    std::vector<Button> buttons = {
        Button(L"старт", font) ,
        Button(L"настройки", font) ,
        Button(L"выйти", font)
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

sf::Font snake::creatFont(const ConfigReader &config) {
    sf::Font font;
    font.loadFromFile(findString("FONT_NAME", config));
    return font;
}

snake::DrawMap snake::creatDrawBackground(sf::RenderWindow &window, snake::TileSet &tile_set, const snake::Map& background, const ConfigReader &config) {
    snake::settings::MapSettings back_conf = snake::settings::loadMapSettings(config, "BACKGROUND");
    return {window, tile_set, background, back_conf._pos_to_tiles};
}

snake::Menu::Menu(sf::RenderWindow& window, ConfigReader &config)
    : _window_ref(window)
    , _font(creatFont(config))
    , _buttons(std::move(creatDefaultButtons(_font)))
    , _tile_set_button(snake::settings::creatTileSet(snake::settings::loadButtonSettings(config)._tiles))
    , _draw_buttons(creatDrawButton(_window_ref, _tile_set_button, _buttons, config))
    , _background(std::move(snake::settings::creatMap(config, "BACKGROUND"))) 
    , _tile_set_background(snake::settings::creatTileSet(snake::settings::loadMapSettings(config, "BACKGROUND")._tiles))
    , _draw_back(creatDrawBackground(_window_ref, _tile_set_background, _background, config)) {
    // устанавливаем все кнопки на свои места
    setButtonsToPossition();
    _mouse_pos = sf::Mouse::getPosition(_window_ref);
}

snake::settings::GAME_STATE snake::Menu::update([[maybe_unused]]float time, sf::Event& event) {
    // рисуем фон
    _draw_back.Draw();
    // определяем положение мышки
    _mouse_pos = sf::Mouse::getPosition(_window_ref);
    settings::GAME_STATE state = settings::GAME_STATE::MENU;
    
    // обрабатываем наведение мышки на кнопку
    proccesSelect();

    for (Button& b : _buttons) {
        state = click(b, event, state);
    }

    for (DrawButton& draw_button : _draw_buttons) {
        draw_button.Draw();
    }

    return state;
}

void snake::Menu::setButtonsToPossition() {
    for (size_t i = 0; i < _draw_buttons.size(); ++i) {
        _draw_buttons[i].placeButtonVertically(snake::LineSegmentInfo(static_cast<int>(i + 1)));
    }
}

bool snake::Menu::isCursorOverButton(const Button& button) const {
    sf::Vector2f pos_button = button.getPosition();
    sf::Vector2u size_of_button = _tile_set_button.getScaledSize();
    return _mouse_pos.y > static_cast<int>(pos_button.y) 
        && _mouse_pos.y < (static_cast<int>(pos_button.y) + static_cast<int>(size_of_button.y))
        && _mouse_pos.x > static_cast<int>(pos_button.x)
        && _mouse_pos.x < (static_cast<int>(pos_button.x) + static_cast<int>(size_of_button.x));
}

void snake::Menu::proccesSelect() {
    for (Button& b : _buttons) {
        if (b.getState() == BUTTON_STATES::ACTIVE) {
            break;
        }
        if (isCursorOverButton(b)) {
            b.setState(BUTTON_STATES::FOCUS);
        } else {
            b.setState(BUTTON_STATES::NORMAL);
        }
    }
}

snake::settings::GAME_STATE snake::Menu::click(Button &button, sf::Event &event, settings::GAME_STATE &game_state) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            if (isCursorOverButton(button)) {
                button.setState(BUTTON_STATES::ACTIVE);
            }
        }
    }
    // если кнопка отжата, ещё раз проверяем лежит ли курсор на ней
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            if (isCursorOverButton(button) && button.getState() == BUTTON_STATES::ACTIVE) {
                game_state = chooseAction(button);
            }
            button.setState(BUTTON_STATES::NORMAL);
        }
    }
    return game_state;
}

snake::settings::GAME_STATE snake::Menu::chooseAction(Button &button) {
    sf::String button_text = button.getText().getString();
    if (button_text == L"старт" || button_text == L"start") {
        return settings::GAME_STATE::GAME;
    } else if (button_text == L"настройки" || button_text == L"settings") {
        return settings::GAME_STATE::SETTING;
    } else {
        return settings::GAME_STATE::EXIT;
    }
}
