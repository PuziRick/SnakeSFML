#include <SFML/Graphics.hpp>

#include "settings.h"
#include "engine.h"
#include "config_reader.h"

#include <memory>
#include <iostream>
#include <sstream>

int main() {
    snake::Engine snake(snake::settings::LoaderSettings());
    snake.start();
}