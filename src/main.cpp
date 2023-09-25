#include <SFML/Graphics.hpp>
/*
#include "settings.h"
#include "engine.h"
#include "config_reader.h"


int main() {
    snake::ConfigReader config("config.txt");
    snake::Engine snake(snake::settings::LoaderSettings(config));
    snake.start();
}

*/

#include "button.h"
#include "draw.h"
#include <map>
#include <iostream>

int main() {
    const sf::Vector2u WIDESCREEN(960, 640);
    sf::RenderWindow window(sf::VideoMode(WIDESCREEN.x, WIDESCREEN.y), "test_button");

    const sf::Vector2u TILES_SIZE(710, 140);
    const float SCALE = 0.25f;

    std::map<snake::BUTTON_STATES, sf::Vector2u> pos_to_tiles = {
        {snake::BUTTON_STATES::NORMAL, {0,0}} ,
        {snake::BUTTON_STATES::ACTIVE, {0,1}} ,
        {snake::BUTTON_STATES::FOCUS, {0,2}}
    };

    sf::Vector2i pos(static_cast<int>(WIDESCREEN.x - TILES_SIZE.x) / 2, static_cast<int>(WIDESCREEN.y - TILES_SIZE.y) / 3);
    std::cout << "[" << pos.x << "," << pos.y << "]" << std::endl;

    snake::Button button("Старт", pos);
    snake::TileSet tiles("images/button.png", TILES_SIZE, SCALE);

    snake::DrawButton drawa(window, tiles, button, pos_to_tiles);

    bool is_pressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                is_pressed = !is_pressed;
                if (is_pressed) {
                    button.setState(snake::BUTTON_STATES::ACTIVE);
                } else {
                    button.setState(snake::BUTTON_STATES::NORMAL);
                }
            }
        }
        window.clear();
        drawa.Draw();
        window.display();
    }
}