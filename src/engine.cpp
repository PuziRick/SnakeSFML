#include "engine.h"
#include <iostream>

snake::RandomGen::RandomGen(sf::Vector2u map_size) 
    : gen(rd())
    , dist_x(0, static_cast<unsigned int>(map_size.x))
    , dist_y(0, static_cast<unsigned int>(map_size.y)) {
}

sf::Vector2i snake::RandomGen::getXY() {
    sf::Vector2i rslt(static_cast<int>(dist_x(gen)), static_cast<int>(dist_y(gen)));
    return rslt;
}

snake::TileSet snake::creatTileSet(snake::settings::TileSetSettings tiles_setting) {
    snake::TileSet tileset(tiles_setting._image_name, tiles_setting._tile_size, tiles_setting._scale);
    return tileset;
}

snake::Snake snake::creatSnake(snake::settings::SnakeSettings snake_setting) {
    snake::Snake snake(snake_setting._started_position, snake_setting._started_size);
    return snake;
}

snake::Map snake::creatMap(snake::settings::MapSettings map_setting) {
    snake::Map _map(map_setting._size_of_map, map_setting._num_of_textures);
    return _map;
}

snake::DrawMap snake::creatDrawMap(snake::Map &map, snake::TileSet& tiles, sf::RenderWindow &window, snake::settings::MapSettings mapSet) {
    snake::DrawMap drawMap(window, tiles, map, mapSet._pos_to_tiles);
    return drawMap;
}

snake::DrawSnake snake::creatDrawSnake(snake::Snake &snake, snake::TileSet& tiles, sf::RenderWindow &window, snake::settings::SnakeSettings snakeSet) {
    snake::DrawSnake drawSnake(window, tiles, snake, snakeSet._pos_to_tiles);
    return drawSnake;
}

snake::Engine::Engine(snake::settings::GameSettings settings) 
    : _window(sf::VideoMode(settings._window_conf._widescreen_x, settings._window_conf._widescreen_y), settings._window_conf._window_name) 
    , _snake(creatSnake(settings._snake_conf))
    , _map(creatMap(settings._map_conf))
    , _snake_tiles(creatTileSet(settings._snake_conf._tiles))
    , _map_tiles(creatTileSet(settings._map_conf._tiles))
    , _snake_draw(creatDrawSnake(_snake, _snake_tiles, _window, settings._snake_conf))
    , _map_draw(creatDrawMap(_map, _map_tiles, _window, settings._map_conf))
    , _random(_map.getSizeOfMap()) {
    auto new_map = settings::creatMap(_map.getSizeOfMap().x, _map.getSizeOfMap().y);
    _map.loadMap(new_map);
}

void snake::Engine::start() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _window.clear();
        _map_draw.Draw();
        _snake_draw.Draw();
        
        _window.display();
    }
}