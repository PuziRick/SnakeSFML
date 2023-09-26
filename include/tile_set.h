#pragma once
#include <SFML/Graphics.hpp>

namespace snake {

class TileSet {
private:
    sf::Vector2u _tile_size;                                                            // размер спрайта
    sf::Texture _texture;                                                               // текстура
    sf::Sprite _sprite;                                                                 // спрайт
    sf::Vector2f _scale;                                                                // масштаб {scale.x, scale.y}
public:
    TileSet(const std::string& image_name, sf::Vector2u tile_size, sf::Vector2f scale);
    TileSet(const std::string& image_name, sf::Vector2u tile_size, float scale);        // на случай если масштабирование по вертикали и горизонтали одинаковое

    sf::Sprite& getSprite(sf::Vector2u possition);                                      // возвращает pos спрайт из загруженного тайлсета
    sf::Vector2u getTileSize() const;                                                   // возвращает размер спрайта до скелинга
    sf::Vector2f getScale() const;                                                      // возвращает масштаб
    sf::Vector2u getScaledSize() const;                                                 // возвращает размер спрайта после скелинга
};

} // конец namespace snake
