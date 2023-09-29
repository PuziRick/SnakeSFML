#include "game.h"
#include "settings.h"
#include "menu.h"
#include "engine.h"

snake::Game::Game(const std::string& config_name = "config.txt") 
    : _config(config_name) {

    // Создаем окно
    settings::WindowSettings settings = settings::loadWindowSettings(_config);
    sf::RenderWindow _window(sf::VideoMode(settings._widescreen_x, settings._widescreen_y), settings._window_name);

    // Задаем игровое время
    sf::Clock clock;
    float global_time = 0;    // глобальное время

    // Создаем стартовое меню
    Menu menu(_window, _config);
    // Создаем объект игрового движка
    Engine engine(_window, _config);


    // текущее состояние игры
    settings::GAME_STATE game_state = settings::GAME_STATE::MENU;

    while (_window.isOpen()) {
        float time = static_cast<float>(clock.getElapsedTime().asMicroseconds()); // вернуть прошедшее время в мкс
        clock.restart();      // перезагрузить время
        time /= 1000;         // полученное время нормируем (подобрано вручную)
        global_time += time;  // и прибовляем к глобальному времени

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        _window.clear();

        switch (game_state) {
            case settings::GAME_STATE::MENU :
            case settings::GAME_STATE::SETTING :
                game_state = menu.update(global_time, event);
                break;
            case settings::GAME_STATE::GAME :
                game_state = engine.update(global_time);
                break;
            case settings::GAME_STATE::EXIT :
                _window.close();
                break;
            default: game_state = menu.update(global_time, event);
        };

        _window.display();
    }
}