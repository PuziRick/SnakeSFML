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
#include <string>

int main() {
    const sf::Vector2u WIDESCREEN(960, 640);
    sf::RenderWindow window(sf::VideoMode(WIDESCREEN.x, WIDESCREEN.y), "test_button");

    const sf::Vector2u TILES_SIZE(645, 140);
    float SCALE = 1.0f;

    std::map<snake::BUTTON_STATES, sf::Vector2u> pos_to_tiles = {
        {snake::BUTTON_STATES::NORMAL, {0,0}} ,
        {snake::BUTTON_STATES::ACTIVE, {0,1}} ,
        {snake::BUTTON_STATES::FOCUS, {0,2}}
    };

    snake::Button button(L"cтарт");
    snake::TileSet tiles("images/button.png", TILES_SIZE, SCALE);

    snake::DrawButton drawButton(window, tiles, button, pos_to_tiles);
    //drawButton.CenterButtom();
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
        drawButton.Draw();
        window.display();
    }
}