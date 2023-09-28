#include "game.h"
#include "settings.h"

snake::Game::Game(const std::string& config_name = "config.txt") 
    : _config(config_name) {

    // Создаем окно
    settings::WindowSettings settings = settings::loadWindowSettings(_config);
    sf::RenderWindow _window(sf::VideoMode(settings._widescreen_x, settings._widescreen_y), settings._window_name);
    // Задаем игровое время
    //sf::Clock clock;
    //float global_time = 0;    // глобальное время

    // Создаем стартовое меню
    Menu menu(_window, _config);
    // текущее состояние
    GAME_STATE game_state = GAME_STATE::MENU;

    while (_window.isOpen()) {
        /*
        float time = static_cast<float>(clock.getElapsedTime().asMicroseconds()); // вернуть прошедшее время в мкс
        clock.restart();      // перезагрузить время
        time /= 1000;         // полученное время нормируем (подобрано вручную)
        global_time += time;  // и прибовляем к глобальному времени
        */
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _window.clear();

        if (game_state == GAME_STATE::MENU) {
            menu.update();
        }

        _window.display();
    }
}