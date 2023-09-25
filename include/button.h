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
    Button(const std::string& text, const sf::Vector2i& pos = {0,0}, BUTTON_STATES state = BUTTON_STATES::NORMAL);
    std::string getText() const;
    BUTTON_STATES getState() const;
    void setState(BUTTON_STATES state);
    sf::Vector2i getPosition() const;
    void setPosition(sf::Vector2i pos);
private:
    std::string _text;
    BUTTON_STATES _state;
    sf::Vector2i _position;
};

} // конец namespace snake