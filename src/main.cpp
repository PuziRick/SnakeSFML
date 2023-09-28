#include <SFML/Graphics.hpp>

#include "game.h"

int main() {
    snake::Game game("config.txt");
}

/*
#include "settings.h"
#include "engine.h"
#include "config_reader.h"


int main() {
    snake::ConfigReader config("config.txt");
    snake::Engine snake(snake::settings::LoaderSettings(config));
    snake.start();
}



#include "button.h"
#include "draw.h"
#include <map>
#include <iostream>
#include <string>
#include <random>

int main() {
    const sf::Vector2u WIDESCREEN(960, 640);
    sf::RenderWindow window(sf::VideoMode(WIDESCREEN.x, WIDESCREEN.y), "test_button");

    const sf::Vector2u TILES_SIZE(645, 140);
    float SCALE = 0.55f;

    std::map<snake::BUTTON_STATES, sf::Vector2u> pos_to_tiles = {
        {snake::BUTTON_STATES::NORMAL, {0,0}} ,
        {snake::BUTTON_STATES::ACTIVE, {0,1}} ,
        {snake::BUTTON_STATES::FOCUS, {0,2}}
    };

    snake::Map background({30, 16}, 1);
    snake::TileSet tiles_back("images/background.png", {32,40}, 4.0f);
    std::vector<sf::Vector2u> pos_to_back = {{0,0}};
    snake::DrawMap drawBack(window, tiles_back, background, pos_to_back);

    snake::Button button_n(L"cтарт");
    snake::Button button_s(L"Настройки");
    snake::Button button_q(L"Выйти");
    snake::TileSet tiles("images/button.png", TILES_SIZE, SCALE);

    snake::DrawButton drawButton_n(window, tiles, button_n, pos_to_tiles);
    drawButton_n.placeButtonVertically(1);
    snake::DrawButton drawButton_s(window, tiles, button_s, pos_to_tiles);
    drawButton_s.placeButtonVertically(2);
    snake::DrawButton drawButton_q(window, tiles, button_q, pos_to_tiles);
    drawButton_q.placeButtonVertically(3);

    bool is_pressed_n = false;
    bool is_pressed_s = false;
    bool is_pressed_q = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                is_pressed_n = !is_pressed_n;
                if (is_pressed_n) {
                    button_n.setState(snake::BUTTON_STATES::ACTIVE);
                } else {
                    button_n.setState(snake::BUTTON_STATES::NORMAL);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                is_pressed_s = !is_pressed_s;
                if (is_pressed_s) {
                    button_s.setState(snake::BUTTON_STATES::ACTIVE);
                } else {
                    button_s.setState(snake::BUTTON_STATES::NORMAL);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                is_pressed_q = !is_pressed_q;
                if (is_pressed_q) {
                    button_q.setState(snake::BUTTON_STATES::ACTIVE);
                } else {
                    button_q.setState(snake::BUTTON_STATES::NORMAL);
                }
            }
        }
        window.clear();
        drawBack.Draw();
        drawButton_n.Draw();
        drawButton_s.Draw();
        drawButton_q.Draw();
        window.display();
    }
}
*/