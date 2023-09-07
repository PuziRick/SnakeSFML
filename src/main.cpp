#include <SFML/Graphics.hpp>
#include "snake.h"
#include "draw.h"
#include <iostream>
#include <vector>
#include <map>

std::vector<std::vector<int>> creatMap(size_t width, size_t height) {
    std::vector<std::vector<int>> result_map;
    result_map.reserve(height);
    for (size_t y = 0; y < height; ++y) {
        std::vector<int> map_x;
        map_x.reserve(width);
        for (size_t x = 0; x < width; ++x) {
            if (y == 0 || y + 1 == height || x == 0 || x + 1 == width) {
                map_x.push_back(0);
            } else if (y % 2 == 0) {
                map_x.push_back(((x % 2 == 0) ? 2 : 1));
            } else {
                map_x.push_back(y % 2 + x % 2);
            }
        }
        result_map.push_back(std::move(map_x));
    }
    return result_map;
}

int main() {
    snake::Snake _snake({0,0},4);
    snake::TileSet _tile_set_snake("images/snake.png", {64,64}, 0.5f);
    snake::TileSet _tile_set_map("images/grass.png", {64,64}, 0.5f);
    sf::RenderWindow _window(sf::VideoMode(630, 630), "Snake");

    std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> pos_tiles = {
        {snake::TypeOfSnakeBodyTileset::HEAD_UP, {0,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_DOWN, {2,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_LEFT, {3,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_RIGHT, {1,0}},
        {snake::TypeOfSnakeBodyTileset::TAIL_UP, {0,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_DOWN, {2,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_LEFT, {3,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_RIGHT, {1,1}},
        {snake::TypeOfSnakeBodyTileset::HORIZONTAL_BODY, {1,3}},
        {snake::TypeOfSnakeBodyTileset::VERTICAL_BODY, {0,3}},
        {snake::TypeOfSnakeBodyTileset::RUSSIAN_G_LETTER_BODY, {1,2}},
        {snake::TypeOfSnakeBodyTileset::INVERSE_RUSSIAN_G_LETTER_BODY, {2,2}},
        {snake::TypeOfSnakeBodyTileset::L_BODY, {0,2}},
        {snake::TypeOfSnakeBodyTileset::INVERSE_L_BODY, {3,2}}
    };

    std::vector<sf::Vector2u> pos_map = {{3,0}, {0,0}, {5,0}};

    snake::Map _map({20,20}, 3);
    auto tmp = creatMap(20,20);
    _map.loadMap(tmp);

    for (unsigned int y = 0; y < _map.getSizeOfMap().y; ++y) {
        for (unsigned int x = 0; x < _map.getSizeOfMap().x; ++x) {
            std::cout << _map.at({x,y}) << " ";
        }
        std::cout << std::endl;
    }

    snake::DrawSnake draw_snake(_window, _tile_set_snake, _snake, pos_tiles);
    snake::DrawMap draw_map(_window, _tile_set_map, _map, pos_map);
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _window.clear();
        draw_map.Draw();
        draw_snake.Draw();
        
        _window.display();
    }
}