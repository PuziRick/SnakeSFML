#pragma once
#include <SFML/Graphics.hpp>

#include "my_test_framework.h"
#include "tile_set.h"
#include <iostream>
#include <sstream>

using std::literals::string_literals::operator""s;

bool checkErrorStream(std::stringstream& error) {
    return error.str() == "FATAL ERROR - IMAGE IS COULDN'T BE FIND\n";
}

void TestTileSetInitialization() {
    sf::Vector2u size_of_tiles(20u,20u);      // задаем размер тайлов
    sf::Vector2f scale(1.,1.);                // задаем масштаб по вертикали и горизонтали

    // сохраняем старый поток std::cerr в отдельную переменную
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf();

    // Проверка НЕсуществующего тайлсета
    {
        // создаем stringstream для перехвата std::cerr из конструктора TileSet
        std::stringstream errorStream;
        // Перенаправляем std::cerr в пользовательский поток
        std::cerr.rdbuf(errorStream.rdbuf());

        // создаем тайлсет, с названием которого гарантировано нет
        snake::TileSet fatal_error_tile_set("communism.png"s, size_of_tiles, scale);
        ASSERT_HINT(checkErrorStream(errorStream), "The TileSet constructor does not handle the error");

        std::cerr.rdbuf(oldCerrBuffer);
    }

    // Проверка существующего тайлсета
    {
        // создаем stringstream для перехвата std::cerr из конструктора TileSet
        std::stringstream errorStream;
        // Перенаправляем std::cerr в пользовательский поток
        std::cerr.rdbuf(errorStream.rdbuf());

        snake::TileSet tile_set("images/test_images.png"s, size_of_tiles, scale);
        ASSERT_HINT(!checkErrorStream(errorStream), "The TileSet constructor error");
        
        std::cerr.rdbuf(oldCerrBuffer);
    }

    // возвращаем старый поток std::cerr
    std::cerr.rdbuf(oldCerrBuffer);
}

void TestTileSet() {
    RUN_TEST_TAB(TestTileSetInitialization,1);
}