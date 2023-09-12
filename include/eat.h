#pragma once
#include <SFML/Graphics.hpp>

namespace snake {

struct Eat {
    Eat(sf::Vector2i coord, size_t hungry_value = 1);
    sf::Vector2i _coordinate;                 // координаты еда
    size_t _hungry_value;                     // величина сытности еды (насколько увеличится змейка)
};

} // конец пространства имен snake
