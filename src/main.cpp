#include <SFML/Graphics.hpp>

#include "settings.h"
#include "engine.h"
#include "config_reader.h"


int main() {
    snake::ConfigReader config("config.txt");
    snake::Engine snake(snake::settings::LoaderSettings(config));
    snake.start();
}