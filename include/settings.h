#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

#include "snake.h"
#include "map.h"
#include "draw.h"
#include "tile_set.h"
#include "config_reader.h"

namespace snake {
namespace settings {

//=============================================================================================================
//                                           СТРУКТУРЫ НАСТРОЕК
//=============================================================================================================

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

struct EatSettings {
    EatSettings(TileSetSettings tile_set, std::vector<sf::Vector2u>& pos_to_tile);
    TileSetSettings _tiles;                  // тайлсет
    std::vector<sf::Vector2u> _pos_to_tiles; // координаты тайлов в тайлсете
};

// скорость игры (подобрана вручную)
enum class GAME_SPEED : int {
    NORMAL = 120,
    FAST = 80,
    SLOWLY = 180
};

// Общие настройки
struct GameSettings {
    GameSettings(SnakeSettings snake_conf, MapSettings map_conf, WindowSettings window_conf, EatSettings eat_conf ,GAME_SPEED game_speed);
    SnakeSettings _snake_conf;     // настройки змейки
    MapSettings _map_conf;         // настройки карты
    WindowSettings _window_conf;   // настройки окна
    EatSettings _eat_conf;         // тайлсет еды
    GAME_SPEED _game_speed;        // скорость игры
};

// настройки для кнопок
struct ButtonSettings {
    ButtonSettings(TileSetSettings tile_set, std::map<BUTTON_STATES, sf::Vector2u>& _pos_to_tiles);
    TileSetSettings _tiles;                              // тайлсет
    std::map<BUTTON_STATES, sf::Vector2u> _pos_to_tiles; // координаты тайлов в тайлсете
};

//=============================================================================================================
//                                        ФУНКЦИИ ЗАГРУЗКИ ДАННЫХ
//=============================================================================================================

// Основные функции загрузки данных
WindowSettings loadWindowSettings(const snake::ConfigReader& config);
ButtonSettings loadButtonSettings(const snake::ConfigReader& config);
MapSettings loadMapSettings(const snake::ConfigReader& config, const std::string& prefix_name = "MAP");
SnakeSettings loadSnakeSettings(const snake::ConfigReader& config);

GameSettings LoaderSettings(const snake::ConfigReader& config);

//=============================================================================================================
//                                        ФУНКЦИИ СОЗДАЮЩИЕ ОБЪЕКТЫ
//=============================================================================================================

Map creatMap(const ConfigReader& config, const std::string& prefix_name = "MAP");
TileSet creatTileSet(TileSetSettings tiles_setting);
snake::Snake creatSnake(const ConfigReader& config);

//=============================================================================================================
//                                       ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
//=============================================================================================================
// Конверторы
TypeOfSnakeBodyTileset convertStringToTypeOfSnake(const std::string& type_str);
GAME_SPEED convertStringToGameSpeed(const std::string& type_str);
BUTTON_STATES converStringToButtonStat(const std::string& type_str);

// создает map для заполнения SNAKE_POS_TILES
std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> creatSnakeTilesetPos(const snake::ConfigReader& config, const std::string& name);
// создает вектор координат тайлов 
std::vector<sf::Vector2u> creatPosOfTiles(const snake::ConfigReader& config, const std::string& name);
// создаем map для заполнения BUTTON_POS_TILES
std::map<snake::BUTTON_STATES, sf::Vector2u> creatButtonPosOfTiles(const snake::ConfigReader& config, const std::string& name);

} // конец namespace settings
} // конец namespace snake