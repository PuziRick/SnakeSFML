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

bool snake::Snake::grow(size_t value) {
    for (size_t i = 0; i < value; ++i) {
        addBodyToEnd();
    }
    
    // Возвращает true если рост прошел успешно
    return !isOuroboros();
}

bool snake::Snake::move(snake::Direction dir) {
    // если пытаются переместиться во внутрь змейки, игнарирует input
    if (isOppositeDirection(dir)) {
        dir = _snake.front()._direction;
    }

    Direction prev_dir = _snake.front()._direction;      // направления предыдущего звена змейки
    bool is_head = true;

    for (Body& snake_body : _snake) {
        if (is_head) {
            moveBodyInToDirection(snake_body, dir);
            is_head = false; 
        } else {
            Direction tmp_dir = snake_body._direction;   // Сохраняем текущее направление тела
            moveBodyInToDirection(snake_body, prev_dir); // Перемещаем тело по направления предыдущего звена
            prev_dir = tmp_dir;                          // Ранее сохраненное направление меняем
        }
    }

    return !isOuroboros();
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

void snake::Snake::addBodyToEnd() {
    // Новая часть змейки появляется в противоположной части от движения последнего звена змейки
    // направление тоже что и у последнего звена
    sf::Vector2i pos_last_el = _snake.back()._position;
    Direction dir_last_el = _snake.back()._direction;

    switch (dir_last_el) {
        case Direction::UP    : pos_last_el.y += 1; break;
        case Direction::DOWN  : pos_last_el.y -= 1; break;
        case Direction::LEFT  : pos_last_el.x += 1; break;
        case Direction::RIGHT : pos_last_el.x -= 1; break;
    }

    _snake.push_back(Body(pos_last_el, dir_last_el));
}

bool snake::Snake::isOppositeDirection(snake::Direction dir) const {
    if (dir == Direction::LEFT && _snake.front()._direction == Direction::RIGHT) {
        return true;
    }
    if (dir == Direction::RIGHT && _snake.front()._direction == Direction::LEFT) {
        return true;
    }
    if (dir == Direction::UP && _snake.front()._direction == Direction::DOWN) {
        return true;
    }
    if (dir == Direction::DOWN && _snake.front()._direction == Direction::UP) {
        return true;
    }
    return false;
}

void snake::Snake::moveBodyInToDirection(snake::Body &body, snake::Direction dir) {
    switch (dir) {
        case Direction::UP    : --body._position.y; break;
        case Direction::DOWN  : ++body._position.y; break;
        case Direction::LEFT  : --body._position.x; break; 
        case Direction::RIGHT : ++body._position.x; break;
    }
    body._direction = dir;
}