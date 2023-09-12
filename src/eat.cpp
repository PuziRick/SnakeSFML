#include "eat.h"

snake::Eat::Eat(sf::Vector2i coord, size_t hungry_value)
    : _coordinate(coord)
    , _hungry_value(hungry_value) {
}