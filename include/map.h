#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace snake {

class Map {
private:
    std::vector<std::vector<int>> _map;
public:
    Map(sf::Vector2u size_of_map, size_t num_of_textures = 1u);
    sf::Vector2u getSizeOfMap() const;                                                               // возвращает размер игрового поля
    bool isOutOfMap(sf::Vector2i pos) const;                                                         // лежит ли указанная координата в игровом поле, true - если не лежит
    int at(sf::Vector2u pos);                                                                        // доступ к ячейки карты с координатой pos
    void createNewMap(sf::Vector2u size_of_map, size_t num_of_textures);                             // генерирует новую карту
    const std::vector<std::vector<int>>& getMap() const;                                             // доступ к карте в виде константной ссылки
private:
    static std::vector<std::vector<int>> generateMap(sf::Vector2u size_of_map, size_t num_of_text);  // вспомогательный метод создаёт случайный массив для новой карты
};

} // конец namespace snake