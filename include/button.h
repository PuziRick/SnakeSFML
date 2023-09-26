#pragma once

#include "tile_set.h"
#include <SFML/Graphics.hpp>

namespace snake {

enum class BUTTON_STATES {
    NORMAL, 
    FOCUS,
    ACTIVE 
};

class Button {
public:
    Button(const std::wstring& text, const sf::Vector2f& pos = {0,0}, BUTTON_STATES state = BUTTON_STATES::NORMAL, const std::string& font_name = "fonts/Radiotechnika.ttf");

    sf::Text& getText();                 // геттер текста на кнопке
    BUTTON_STATES getState() const;      // геттер состояния кнопки
    void setState(BUTTON_STATES state);  // сеттер состояния кнопки
    sf::Vector2f getPosition() const;    // геттер положения кнопки
    void setPosition(sf::Vector2f pos);  // сеттер положения кнопки
private:
    sf::Text _text;
    sf::Font _font;
    BUTTON_STATES _state;
    sf::Vector2f _position;
};

} // конец namespace snake