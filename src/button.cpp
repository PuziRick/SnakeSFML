#include "button.h"

snake::Button::Button(const std::string &text, const sf::Vector2i& pos, BUTTON_STATES state)
    : _text(text)
    , _state(state)
    , _position(pos) {
}

std::string snake::Button::getText() const {
    return _text;
}

snake::BUTTON_STATES snake::Button::getState() const {
    return _state;
}

void snake::Button::setState(BUTTON_STATES state) {
    _state = state;
}

sf::Vector2i snake::Button::getPosition() const {
    return _position;
}

void snake::Button::setPosition(sf::Vector2i pos) {
    _position = pos;
}