#pragma once
#include <SFML/Graphics.hpp>

#include "my_test_framework.h"
#include "snake.h"


void checkSize(const snake::Snake& _snake, size_t size) {
    // если размер меньше 2 (голова и хвост), принудительно ставиться 3
    if (size < 2) {
        ASSERT_EQUAL_HINT(_snake.getSize(), 3, "The size of the snake does not match the specified one");
    } else {
        ASSERT_EQUAL_HINT(_snake.getSize(), size, "The size of the snake does not match the specified one");
    }
} 

void checkPosition(const snake::Snake& _snake, sf::Vector2i position) {
    // пробегаем по всей змейки и проверяем что все звенья лежат друг за другом
    for (size_t pos = 0; pos < _snake.getSize(); ++pos) {
        ASSERT_HINT(_snake.isSnake(position), "The snake is not in the correct coordinates");
        ++position.y;
    }
    // + проверяем работоспособность isSnake подав на неё позицию вне змейки
    ASSERT_HINT(!_snake.isSnake(position), "The snake is not in the correct coordinates");
}

void checkDirection(const snake::Snake& _snake) {
    // пробегаем по всей змейки и проверяем что все звенья направлены вверх
    for (auto snake_i = _snake.cbegin(); snake_i != _snake.cend(); ++snake_i) {
        ASSERT_HINT(snake_i->_direction == snake::Direction::UP, "The snake is not in the correct direction");
    }
}

void TestSnakeInitialization() {
    size_t count_of_test = 10;
    sf::Vector2i started_pos = {0,0};
    size_t started_size = 0;
    for (size_t test_i = started_size; test_i < count_of_test; ++test_i) {
        snake::Snake snake_tmp(started_pos, test_i);
        checkSize(snake_tmp, test_i);
        checkPosition(snake_tmp, started_pos);
        checkDirection(snake_tmp);
    }
}

void TestSnake() {
    RUN_TEST(TestSnakeInitialization);
}
