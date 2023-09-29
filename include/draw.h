#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "tile_set.h"
#include "snake.h"
#include "map.h"
#include "eat.h"
#include "button.h"

namespace snake {

class Drawable {
public:
    Drawable(sf::RenderWindow& window, snake::TileSet& tile_set);
    virtual ~Drawable() = default;
    virtual void Draw() = 0;
    
    // Вспомогательная функция, устанавливающая спрайт в нужную часть
    static void setSpritePositionAndScale(sf::Sprite& sprite, const sf::Vector2i& position, const sf::Vector2u& tile_size, const sf::Vector2f scale);

    sf::RenderWindow& getWindowRef();
    snake::TileSet& getTileSetRef();
private:
    sf::RenderWindow& _window_ref;    // ссылка на окно для рендера 
    snake::TileSet& _tile_set;        // ссылка на тайл-сет объекта
};

// Все возможные типы тайлсета для змейки
enum class TypeOfSnakeBodyTileset {
    HEAD_UP, HEAD_DOWN, HEAD_LEFT, HEAD_RIGHT, 
    TAIL_UP, TAIL_DOWN, TAIL_LEFT, TAIL_RIGHT,
    HORIZONTAL_BODY,
    VERTICAL_BODY,
    RUSSIAN_G_LETTER_BODY,            // this is 'Г'
    INVERSE_RUSSIAN_G_LETTER_BODY,
    L_BODY,
    INVERSE_L_BODY
};

class DrawSnake final : public Drawable {
public:
    DrawSnake(sf::RenderWindow& window, snake::TileSet& tile_set, const snake::Snake& snake_ref,
              std::map<TypeOfSnakeBodyTileset, sf::Vector2u>& pos_to_tiles);
    void Draw() override;
private:
    const snake::Snake& _snake_ref;                                                       // констатная ссылка на змейку
    std::map<TypeOfSnakeBodyTileset, sf::Vector2u> _position_to_tiles;                    // где в тайлсете лежат нужные части тела

    sf::Vector2u choiceSnakeBodyTileset(std::list<snake::Body>::const_iterator it) const; // возвращает позицию тайла для тела
    sf::Vector2u choiseSnakeHead(snake::Direction dir) const;                             // возвращает позицию тайла для головы
    sf::Vector2u choiseSnakeTail(snake::Direction dir) const;                             // возвращает позицию тайла для хвоста

    static bool isHorizontalDirection(Direction dir);                                     // true если направление горизонтальное
    static bool isVerticalDirection(Direction dir);                                       // true если направление вертикальное
};

class DrawMap final : public Drawable {
public:
    DrawMap(sf::RenderWindow& window, snake::TileSet& tile_set, const snake::Map& map, std::vector<sf::Vector2u>& pos_to_tiles);
    void Draw() override;
private:
    const snake::Map& _map_ref;              // констатнтая ссылка на карту
    std::vector<sf::Vector2u> _pos_to_tiles; // Перечислены позиции с текстурами
};

class DrawEat : public Drawable {
public:
    DrawEat(sf::RenderWindow& window, snake::TileSet& tile_set, snake::Eat& eat, std::vector<sf::Vector2u>& pos_to_tiles);
    void Draw() override;
private:
    snake::Eat& _eat_ref;                    // ссылка на объект "еда"
    std::vector<sf::Vector2u> _pos_to_tiles; // перечисление позиций с текстурами
};

struct LineSegmentInfo {
    LineSegmentInfo(int pos_on_vertical = 1, int num_of_segments = 5);
    int _pos_on_vertical;    // номер сегмента
    int _num_of_segments;    // количество сегментов
};

class DrawButton : public Drawable {
public:
    DrawButton(sf::RenderWindow& window, snake::TileSet& tile_set, snake::Button& button, std::map<snake::BUTTON_STATES, sf::Vector2u>& pos_to_tiles);
    void Draw() override;
    void CenterButtom();  // центрирует кнопку по координатам {x,y}
    void placeButtonVertically(LineSegmentInfo segment_info); // размещает кнопку по вертикали
private:
    Button& _button_ref;                                     // ссылка на кнопку
    std::map<BUTTON_STATES, sf::Vector2u> _pos_to_tiles;     // перечисление позиций с текстурами

    static sf::Vector2f calcCenterCoord(sf::Vector2u size_rect, sf::Vector2f pos_lef_up);  // находит координату центра прямоугольника
    static sf::Vector2f calcLeftUpCoord(sf::Vector2u size_rect, sf::Vector2f pos_center);  // находит координату верхнего левого угла
    void resizeText();      // изменяет разме текста
    void centerText();      // центрирует текст в кнопке
    void changeTextColor(); // изменяет цвет текста
};
} // конец namespace snake