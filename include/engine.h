#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <map>

#include "snake.h"
#include "map.h"
#include "draw.h"
#include "tile_set.h"
#include "settings.h"
#include "eat.h"

namespace snake {

// Функции для создания объектов
TileSet creatTileSet(snake::settings::TileSetSettings tiles_setting);
snake::Snake creatSnake(snake::settings::SnakeSettings snake_setting);
snake::Map creatMap(snake::settings::MapSettings map_setting);
snake::DrawMap creatDrawMap(snake::Map& map, snake::TileSet& tiles, sf::RenderWindow& window, snake::settings::MapSettings mapSet);
snake::DrawSnake creatDrawSnake(snake::Snake& snake, snake::TileSet& tiles, sf::RenderWindow& window, snake::settings::SnakeSettings snakeSet);
snake::DrawEat creatDrawEat(snake::Eat& eat, snake::TileSet& tiles, sf::RenderWindow& window, snake::settings::EatSettings eatSet);

// Объекты для создания случайных координат еды
struct RandomGen {
    RandomGen(sf::Vector2u map_size);

    std::random_device rd;                                // нужно для работы генератора
    std::mt19937 gen;                                     // генератор случайных чисел

    std::uniform_int_distribution<unsigned int> dist_x;   // Диапазон распределений по оси x 
    std::uniform_int_distribution<unsigned int> dist_y;   // Диапазон распределений по оси y

    sf::Vector2i getXY();                                 // Возвращает два числа в указанных диапазона
};

class Engine {
public:
    Engine(settings::GameSettings settings);  // Передаём основные настройки
    void start();                             // основная функция игры
private:
    sf::RenderWindow _window;                 // окно для отрисовки
    Snake _snake;                             // змейка
    Map _map;                                 // карта
    snake::TileSet _snake_tiles;              // тайлсет змейки
    snake::TileSet _map_tiles;                // тайлсет карты
    snake::TileSet _eat_tiles;                // тайлсет еды

    DrawSnake _snake_draw;                    // отрисовщик змейки
    DrawMap _map_draw;                        // отрисовщик карты

    RandomGen _random;                        // генератор координат еды
    Eat _eat;                                 // едa
    DrawEat _eat_draw;                        // отрисовщик еды

    float _game_speed;                        // скорость игры
private:
    bool processInput();                      // обработчик нажатых клавишь
    sf::Vector2i creatFood();                 // создает координаты еды
    bool relocateFromOutsideTheMap();         // если змейка выходит за границу, переместить её с зеркальной стороны
    bool eating();                            // приятного аппетита
};

} // конец namespace snake