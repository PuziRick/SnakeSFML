#include "map.h"
#include <random>  // нужна для генерации карты


std::vector<std::vector<int>> snake::Map::generateMap(sf::Vector2u size_of_map, size_t num_of_text) {
    // Повышаем дебило-устойчивость (защита от меня)
    if (num_of_text == 0) {
        num_of_text = 1;
    }
    // Создаем объекты для генерации случайных чисел
    std::random_device rand_device;
    std::mt19937 generator(rand_device());
    std::uniform_int_distribution<> dist(0, static_cast<int>(num_of_text - 1));  // диапазон 

    // 
    std::vector<std::vector<int>> map_result;
    map_result.reserve(size_of_map.y);
    
    for (size_t i = 0; i < size_of_map.y; ++i) {
        std::vector<int> tmp_map_x;
        tmp_map_x.reserve(size_of_map.x);
        for (size_t j = 0; j < size_of_map.x; ++j) {
            int elem = dist(generator);
            tmp_map_x.push_back(elem);
        }
        map_result.push_back(std::move(tmp_map_x));
    }
    return map_result;
}

snake::Map::Map(sf::Vector2u size_of_map, size_t num_of_textures) 
    : _map(std::move(generateMap(size_of_map, num_of_textures))) {
}

sf::Vector2u snake::Map::getSizeOfMap() const {
    return {static_cast<unsigned int>(_map.front().size()), static_cast<unsigned int>(_map.size())};
}

bool snake::Map::isOutOfMap(sf::Vector2i pos) const {
    return pos.x >= static_cast<int>(getSizeOfMap().x) 
        || pos.x < 0
        || pos.y >= static_cast<int>(getSizeOfMap().y) 
        || pos.y < 0;
}

int snake::Map::at(sf::Vector2u pos) {
    // может выбросить исключение
    return _map[pos.y][pos.x];
}

int snake::Map::at(sf::Vector2u pos) const {
    return _map[pos.y][pos.x];
}

void snake::Map::createNewMap(sf::Vector2u size_of_map, size_t num_of_textures) {
    _map = std::move(generateMap(size_of_map, num_of_textures));
    num_of_textures = num_of_textures;
}

const std::vector<std::vector<int>> &snake::Map::getMap() const {
    return _map;
}

void snake::Map::loadMap(std::vector<std::vector<int>> &map) {
    _map = std::move(map);
}
