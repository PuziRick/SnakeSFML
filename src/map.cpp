#include "map.h"

snake::Map::Map(sf::Vector2i size_of_map)
    :_size_of_map(size_of_map) {
}

sf::Vector2i snake::Map::getSizeOfMap() const {
    return _size_of_map;
}

bool snake::Map::isOutOfMap(sf::Vector2i pos) const {
    return pos.x >= _size_of_map.x || pos.x < 0 || pos.y >= _size_of_map.y || pos.y < 0;
}