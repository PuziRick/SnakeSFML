#pragma once

#include <SFML/Graphics.hpp>
#include <list>

namespace snake {

// Перечисление возможных направлений движения
enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

// У каждого звена змейки есть направление движения и позиция
struct Body {
    Body(const sf::Vector2i& pos, Direction dir);
    sf::Vector2i _position;
    Direction _direction;
};

class Snake {
private:
    std::list<Body> _snake;                                         // двухсвязаный список с данными змейки
public:
    Snake(sf::Vector2i started_position, size_t started_size = 3);

    bool grow(size_t value = 1);                                    // метод увеличивает змейку на value
    bool move(Direction dir);                                       // перемещение змейки на одну ячейку в указанном направлении

    bool isOuroboros() const;                                       // проверка что змейка ест сама себя (true - если ест)
    bool isSnake(const sf::Vector2i& position) const;               // находится ли в данной координате змейка
    size_t getSize() const;                                         // возвращает размер змейки
    sf::Vector2i getHeadPosition() const;                           // возвращает координату головы змейки

    // для итерирования по змейки
    std::list<Body>::iterator begin();
    std::list<Body>::iterator end();
    std::list<Body>::const_iterator cbegin() const;
    std::list<Body>::const_iterator cend() const;
private:
    void addBodyToEnd();                                            // вспомогательная функция добавляющая новую часть змейки
    bool isOppositeDirection(Direction dir) const;                  // true если движение направлено во внутрь змейки
    void moveBodyInToDirection(Body& body, Direction dir);          // перемещает звено body по направлению dir
};

} // конец namespace snake