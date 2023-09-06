#include <SFML/Graphics.hpp>
#include "snake.h"
#include "draw.h"
#include <iostream>
#include <vector>
#include <map>

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

    std::vector<sf::Vector2u> pos_map = {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {0,2}, {1,2}, {2,2}, {3,2}, {4,2}};

    snake::Map _map({20,20}, 15);

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