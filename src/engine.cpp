#include "engine.h"

snake::RandomGen::RandomGen(sf::Vector2u map_size) 
    : gen(rd())
    , dist_x(0, static_cast<unsigned int>(map_size.x - 1))
    , dist_y(0, static_cast<unsigned int>(map_size.y - 1)) {
}

sf::Vector2i snake::RandomGen::getXY() {
    sf::Vector2i rslt(static_cast<int>(dist_x(gen)), static_cast<int>(dist_y(gen)));
    return rslt;
}

snake::DrawMap snake::creatDrawMap(snake::Map &map, snake::TileSet& tiles, sf::RenderWindow &window, const ConfigReader& config) {
    auto map_conf = settings::loadMapSettings(config);
    snake::DrawMap drawMap(window, tiles, map, map_conf._pos_to_tiles);
    return drawMap;
}

snake::DrawSnake snake::creatDrawSnake(snake::Snake &snake, snake::TileSet& tiles, sf::RenderWindow &window, const ConfigReader& config) {
    auto snake_conf = settings::loadSnakeSettings(config);
    snake::DrawSnake drawSnake(window, tiles, snake, snake_conf._pos_to_tiles);
    return drawSnake;
}

snake::DrawEat snake::creatDrawEat(snake::Eat &eat, snake::TileSet &tiles, sf::RenderWindow &window, const ConfigReader& config) {
    auto eat_conf = settings::loadEatSettings(config);
    snake::DrawEat drawEat(window, tiles, eat, eat_conf._pos_to_tiles);
    return drawEat;
}

snake::Engine::Engine(sf::RenderWindow& window, ConfigReader& config) 
    : _config_ref(config)
    , _window_ref(window) 
    , _snake(settings::creatSnake(_config_ref))
    , _map(settings::creatMap(_config_ref))
    , _snake_tiles(settings::creatTileSet(settings::loadSnakeSettings(_config_ref)._tiles))
    , _map_tiles(settings::creatTileSet(settings::loadMapSettings(_config_ref)._tiles))
    , _eat_tiles(settings::creatTileSet(settings::loadEatSettings(_config_ref)._tiles))
    , _snake_draw(creatDrawSnake(_snake, _snake_tiles, _window_ref, _config_ref))
    , _map_draw(creatDrawMap(_map, _map_tiles, _window_ref, _config_ref))
    , _random(_map.getSizeOfMap())
    , _eat(creatFood(), 1u)
    , _eat_draw(creatDrawEat(_eat, _eat_tiles, _window_ref, _config_ref))
    , _game_speed(static_cast<float>(settings::convertStringToGameSpeed(findString("GAME_SPEED", _config_ref)))) {
}

snake::settings::GAME_STATE snake::Engine::update(float& global_time) {
    // обработка инпутов
    if (global_time > _game_speed) {
        // если змейка умирает закрываем окно
        // to do добавить меню и сделать нормально конец игры
        if (!processInput()) {
            reload();
            return snake::settings::GAME_STATE::MENU;
        }
        // если змейка за границей карты перенести её
        if (!relocateFromOutsideTheMap()) {
            reload();
            return snake::settings::GAME_STATE::MENU;
        }
        // процесс поедания, самый любимый в жизни кота Бориса
        if (!eating()) {
            reload();
            return snake::settings::GAME_STATE::MENU;
        }
        global_time -= _game_speed;
    }
    _map_draw.Draw();
    _eat_draw.Draw();
    _snake_draw.Draw();

    return snake::settings::GAME_STATE::GAME;
}

void snake::Engine::reload() {
    _snake = settings::creatSnake(_config_ref);
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
