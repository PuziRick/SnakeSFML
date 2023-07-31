#include "snake.h"
#include <iterator>

snake::Body::Body(const sf::Vector2i &pos, Direction dir) 
    : _position(pos)
    , _direction(dir) {
}

snake::Snake::Snake(sf::Vector2i started_position, size_t started_size) {
    // если хотим создать змейку меньше 2 (голова и хвост), то принудительно
    // ставим размер равный 3
    if (started_size < 2) {
        started_size = 3;
    }
    // Создаем вертикальную змейку с головой в указанной позиции, 
    // длиной started_size, все звенья направлены вверх
    for (size_t i = 0; i < started_size; ++i) {
        _snake.push_back(Body(started_position, Direction::UP));
        ++started_position.y;
    }
}

bool snake::Snake::isOuroboros() const {
    // Проходим по всем звеньям змейки и проверяем что
    // координаты головы совпадают с координатами тела
    for (auto it = std::next(_snake.begin()); it != _snake.end(); ++it) {
        if (it->_position == _snake.begin()->_position) {
            return true;
        }
    }
    return false;
}

bool snake::Snake::isSnake(const sf::Vector2i& position) const {
    for (const Body& s : _snake) {
        if (s._position == position) {
            return true;
        }
    }
    return false;
}

size_t snake::Snake::getSize() const {
    return _snake.size();
}

sf::Vector2i snake::Snake::getHeadPosition() const {
    return _snake.front()._position;
}

std::list<snake::Body>::iterator snake::Snake::begin() {
    return _snake.begin();
}

std::list<snake::Body>::iterator snake::Snake::end() {
    return _snake.end();
}

std::list<snake::Body>::const_iterator snake::Snake::cbegin() const {
    return _snake.cbegin();
}

std::list<snake::Body>::const_iterator snake::Snake::cend() const {
    return _snake.cend();
}