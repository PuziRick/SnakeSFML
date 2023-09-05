#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "my_test_framework.h"
#include "map.h"

bool EqualOfVectors(const std::vector<std::vector<int>>& left, const std::vector<std::vector<int>>& right) {
    return left == right;
}

bool EqualOfSize(sf::Vector2u left, sf::Vector2u right) {
    return left == right;
}

void TestMapInitialization() {
    sf::Vector2u size_of_map = {100,100};
    size_t num_of_textures = 10;

    snake::Map _map(size_of_map, num_of_textures);
    ASSERT_HINT(EqualOfSize(_map.getSizeOfMap(), size_of_map), "The map of the snake does not match the specified one");
}

void TestMapRandom() {
    // Создаем карту, делаем копию карты и пересоздаем карту
    sf::Vector2u size_of_map = {100,100};
    size_t num_of_textures = 10;
    snake::Map _map(size_of_map, num_of_textures);
    std::vector<std::vector<int>> copy_map(_map.getMap().begin(), _map.getMap().end());

    _map.createNewMap(size_of_map, num_of_textures);
    ASSERT_HINT(!EqualOfVectors(copy_map,_map.getMap()), "Function creatNewMap is fauld");

    size_of_map = {200,200}; // хотим увеличить размер карты
    _map.createNewMap(size_of_map, num_of_textures);
    ASSERT_HINT(EqualOfSize(_map.getSizeOfMap(), size_of_map), "Function creatNewMap is fauld - creat new size");
}

bool CheckRangeOut(int y_first, int y_last, int x_first, int x_last, const snake::Map& _map) {
    for (int y = y_first; y < y_last; ++y) {
        for (int x = x_first; x < x_last; ++x) {
            if (!_map.isOutOfMap({x,y})) {
                return false;
            }
        }
    }
    return true;
}

void TestOutOfMap() {
    sf::Vector2u size_of_map = {100,100};
    size_t num_of_textures = 10;
    snake::Map _map(size_of_map, num_of_textures);
    // проверяем что все координаты внутри карты возвращают false
    for (int y = 0; y < static_cast<int>(size_of_map.y); ++y) {
        for (int x = 0; x < static_cast<int>(size_of_map.x); ++x) {
            ASSERT_HINT(!_map.isOutOfMap({x,y}), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");
        }
    }
    // проверяем точки вне карты
    // 1) x < 0 && y < 0
    ASSERT_HINT(CheckRangeOut(-1 * static_cast<int>(size_of_map.y), 0, -1 * static_cast<int>(size_of_map.x), 0, _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

    // 2) x > size_of_map.x && y > size_of_map.y
    ASSERT_HINT(CheckRangeOut(static_cast<int>(size_of_map.y), static_cast<int>(size_of_map.y * 2), static_cast<int>(size_of_map.x), static_cast<int>(size_of_map.x * 2), _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");
    
    // 3) x < 0 && y > size_of_map.y
    ASSERT_HINT(CheckRangeOut(static_cast<int>(size_of_map.y), static_cast<int>(size_of_map.y * 2), -1 * static_cast<int>(size_of_map.x), 0, _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");
    
    // 4) x > size_of_map.x && y < 0
    ASSERT_HINT(CheckRangeOut(-1 * static_cast<int>(size_of_map.y), 0, static_cast<int>(size_of_map.x), static_cast<int>(size_of_map.x * 2), _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

    // 5) x < 0 && y э [0,size_of_map.y]
    ASSERT_HINT(CheckRangeOut(0, static_cast<int>(size_of_map.y), -1 * static_cast<int>(size_of_map.x), 0, _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

    // 6) x > size_of_map.x && y э [0,size_of_map.y]
    ASSERT_HINT(CheckRangeOut(0, static_cast<int>(size_of_map.y), static_cast<int>(size_of_map.x), static_cast<int>(size_of_map.x * 2), _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

    // 7) x э [0,size_of_map.x] && y < 0
    ASSERT_HINT(CheckRangeOut(-1 * static_cast<int>(size_of_map.y), 0, 0, static_cast<int>(size_of_map.x), _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

    // 8) x э [0,size_of_map.x] && y > size_of_map.y
    ASSERT_HINT(CheckRangeOut(static_cast<int>(size_of_map.y), static_cast<int>(size_of_map.y * 2), 0, static_cast<int>(size_of_map.x), _map), "Error in the isOutOfMap method, the coordinate inside the map is not defined correctly");

}

void TestMap() {
    RUN_TEST_TAB(TestMapInitialization,1);
    RUN_TEST_TAB(TestMapRandom,1);
    RUN_TEST_TAB(TestOutOfMap,1);
}