#include <SFML/Graphics.hpp>
#include "snake.h"
#include <iostream>

int main() {
    sf::Vector2i snake_position = {0,0};
    size_t snake_size = 3;
    snake::Snake tested_snake(snake_position, snake_size);

    for (size_t i = 0; i < snake_size + 1; ++i) {
        std::cout << std::boolalpha << tested_snake.isSnake(snake_position) << std::endl;
        ++snake_position.y;
    }
    std::cout << std::boolalpha << (snake_size == tested_snake.getSize()) << std::endl;
}