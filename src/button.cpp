#include "button.h"

snake::Button::Button(const std::wstring &text, const sf::Vector2f& pos, BUTTON_STATES state, const std::string& font_name)
    : _state(state)
    , _position(pos) {
    _font.loadFromFile(font_name);
    _text.setFont(_font);
    _text.setFillColor(sf::Color::White);
    _text.setString(sf::String(text));
    _text.setStyle(sf::Text::Regular);
}

sf::Text& snake::Button::getText() {
    return _text;
}

snake::BUTTON_STATES snake::Button::getState() const {
    return _state;
}

void snake::Button::setState(BUTTON_STATES state) {
    _state = state;
}

sf::Vector2f snake::Button::getPosition() const {
    return _position;
}

void snake::Button::setPosition(sf::Vector2f pos) {
    _position = pos;
}

void snake::Button::setTextColor(sf::Color color) {
    _text.setFillColor(color);
}
