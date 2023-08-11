#pragma once

#include <SFML/Graphics.hpp>

namespace snake {


// класс Map содержит только информацию о количестве клеток по горизонтали и вертикали
// может поделиться этим большим секретом и сказать лежит ли указанная координата в данном диапазоне

class Map {
private:
    sf::Vector2i _size_of_map;
public:
    Map(sf::Vector2i size_of_map);
    sf::Vector2i getSizeOfMap() const;        // возвращает размер игрового поля
    bool isOutOfMap(sf::Vector2i pos) const;  // лежит ли указанная координата в игровом поле
};

} // конец namespace snake