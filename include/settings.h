#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

#include "snake.h"
#include "map.h"
#include "draw.h"
#include "tile_set.h"

namespace snake {
namespace settings {

// Настройки необходимые для создания окна
struct WindowSettings {
    WindowSettings(sf::Vector2u widescreen, std::string name);
    unsigned int _widescreen_x;           // разрешение экрана по x
    unsigned int _widescreen_y;           // разрешение экрана по y
    std::string _window_name;    // название окна
};

// Настройки необходимые для создания окна
struct TileSetSettings {
    TileSetSettings(std::string image_name, sf::Vector2u tile_size, float scale);
    std::string _image_name;      // название файла с текстурами
    sf::Vector2u _tile_size;      // размер одного тайла
    float _scale;                 // масштаб
};

// Настройки необходимые для создания змейки
struct SnakeSettings {
    SnakeSettings(TileSetSettings tile_set, std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u>& pos_to_tile, sf::Vector2i pos, size_t size = 3u);
    sf::Vector2i _started_position;                                      // начальное положение змейки
    size_t _started_size;                                                // размер змейки
    TileSetSettings _tiles;                                              // тайлсет
    std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> _pos_to_tiles; // координаты тайлов в тайлсете
};

// Настройки необходимые для создания карты
struct MapSettings {
    MapSettings(TileSetSettings tile_set, std::vector<sf::Vector2u>& pos_to_tile, sf::Vector2u size_of_map, size_t num_of_textures = 1);
    sf::Vector2u _size_of_map;               // размеры карты
    size_t _num_of_textures;                 // количество текстур для карты
    TileSetSettings _tiles;                  // тайлсет
    std::vector<sf::Vector2u> _pos_to_tiles; // координаты тайлов в тайлсете
};

// Общие настройки
struct GameSettings {
    GameSettings(SnakeSettings snake_conf, MapSettings map_conf, WindowSettings window_conf);
    SnakeSettings _snake_conf;     // настройки змейки
    MapSettings _map_conf;         // настройки карты
    WindowSettings _window_conf;   // настройки окна
};


std::vector<std::vector<int>> creatMap(size_t width, size_t height);

// to do сделать удобный загрузчик настроек (например из файла)
GameSettings LoaderSettings();

} // конец namespace settings
} // конец namespace snake