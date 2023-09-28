#include "engine.h"
/*
snake::RandomGen::RandomGen(sf::Vector2u map_size) 
    : gen(rd())
    , dist_x(0, static_cast<unsigned int>(map_size.x - 1))
    , dist_y(0, static_cast<unsigned int>(map_size.y - 1)) {
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

snake::DrawEat snake::creatDrawEat(snake::Eat &eat, snake::TileSet &tiles, sf::RenderWindow &window, snake::settings::EatSettings eatSet) {
    snake::DrawEat drawEat(window, tiles, eat, eatSet._pos_to_tiles);
    return drawEat;
}

snake::Engine::Engine(snake::settings::GameSettings settings) 
    : _window(sf::VideoMode(settings._window_conf._widescreen_x, settings._window_conf._widescreen_y), settings._window_conf._window_name) 
    , _snake(std::move(creatSnake(settings._snake_conf)))
    , _map(std::move(creatMap(settings._map_conf)))
    , _snake_tiles(creatTileSet(settings._snake_conf._tiles))
    , _map_tiles(creatTileSet(settings._map_conf._tiles))
    , _eat_tiles(creatTileSet(settings._eat_conf._tiles))
    , _snake_draw(creatDrawSnake(_snake, _snake_tiles, _window, settings._snake_conf))
    , _map_draw(creatDrawMap(_map, _map_tiles, _window, settings._map_conf))
    , _random(_map.getSizeOfMap())
    , _eat(creatFood(), 1u)
    , _eat_draw(creatDrawEat(_eat, _eat_tiles, _window, settings._eat_conf))
    , _game_speed(static_cast<float>(settings._game_speed)) {
}

void snake::Engine::start() {
    sf::Clock _clock;
    float _global_time = 0;   // глобальное время

    while (_window.isOpen()) {
        float time = static_cast<float>(_clock.getElapsedTime().asMicroseconds()); // вернуть прошедшее время в мкс
        _clock.restart();                                                          // перезагрузить время
        time /= 1000;                                                              // полученное время нормируем (подобрано вручную)
        _global_time += time;                                                      // и прибовляем к глобальному времени

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        // обработка инпутов
        if (_global_time > _game_speed) {
            // если змейка умирает закрываем окно
            // to do добавить меню и сделать нормально конец игры
            if (!processInput()) {
                _window.close();
            }
            // если змейка за границей карты перенести её
            if (!relocateFromOutsideTheMap()) {
                _window.close();
            }
            // процесс поедания, самый любимый в жизни кота Бориса
            if (!eating()) {
                _window.close();
            }
            _global_time -= _game_speed;
        }

        _window.clear();
        _map_draw.Draw();
        _eat_draw.Draw();
        _snake_draw.Draw();
        
        _window.display();
    }
}

sf::Vector2i snake::Engine::creatFood() {
    // Генерируем случайные числа до тех пор, пока полученная координата не лежит на змейки
    sf::Vector2i rslt = _random.getXY();
    while (_snake.isSnake(rslt)) {
        rslt = _random.getXY();
    }
    return rslt;
}

bool snake::Engine::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        return _snake.move(Direction::UP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        return _snake.move(Direction::DOWN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return _snake.move(Direction::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return _snake.move(Direction::RIGHT);
    }
    
    // если кнопка не нажата движемся по направлению взгяда
    return _snake.move(_snake.begin()->_direction);
}

bool snake::Engine::relocateFromOutsideTheMap() {
    for (auto it = _snake.begin(); it != _snake.end(); ++it) {
        if (_map.isOutOfMap(it->_position)) {
            if (it->_position.x < 0) {
                it->_position.x = static_cast<int>(_map.getSizeOfMap().x - 1);
            } 
            if (it->_position.x >= static_cast<int>(_map.getSizeOfMap().x)) {
                it->_position.x = 0;
            } 
            if (it->_position.y < 0) {
                it->_position.y = static_cast<int>(_map.getSizeOfMap().y - 1);
            } 
            if (it->_position.y >= static_cast<int>(_map.getSizeOfMap().y)) {
                it->_position.y = 0;
            }
        }
    }
    return !_snake.isOuroboros();
}

bool snake::Engine::eating() {
    if (_snake.isSnake(_eat._coordinate)) {
        _eat._coordinate = creatFood();
        return _snake.grow(_eat._hungry_value);
    }
    return true;
}
*/