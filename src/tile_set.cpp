#include <iostream> // для std::cerr
#include "tile_set.h"

snake::TileSet::TileSet(const std::string& image_name, sf::Vector2u tile_size, sf::Vector2f scale)
    :_tile_size(tile_size)
    ,_scale(scale) {
    // Если не получилось прогрузить тайлсет, то создаем красное изображение размером tile_size 
    if (_texture.loadFromFile(image_name)) {
        _sprite.setTexture(_texture);
    } else {
        std::cerr << "FATAL ERROR - IMAGE IS COULDN'T BE FIND" << std::endl;
        sf::Image fatal_error_image;
        fatal_error_image.create(_tile_size.x, _tile_size.y, sf::Color::Red);
        _texture.loadFromImage(fatal_error_image);
        _sprite.setTexture(_texture);
    }
    _sprite.setScale({_scale.x, _scale.y});
}

snake::TileSet::TileSet(const std::string &image_name, sf::Vector2u tile_size, float scale)
    :TileSet(image_name, tile_size, {scale, scale}) {
}

sf::Sprite& snake::TileSet::getSprite(sf::Vector2u pos) {
    // Создаем прямоугольное окно, указывая вверхнюю левую координату и ширину с высотой
    sf::IntRect place_on_texture(static_cast<int>(pos.x * _tile_size.x), static_cast<int>(pos.y * _tile_size.y), static_cast<int>(_tile_size.x), static_cast<int>(_tile_size.y));
    // Выризаем из текстуры нужный прямоугольник
    _sprite.setTextureRect(place_on_texture);

    return _sprite;
}

sf::Vector2u snake::TileSet::getTileSize() const {
    return _tile_size;
}

sf::Vector2f snake::TileSet::getScale() const {
    return _scale;
}