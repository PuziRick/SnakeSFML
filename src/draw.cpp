#include "draw.h"
#include <iterator>

snake::Drawable::Drawable(sf::RenderWindow& window, snake::TileSet& tile_set)
    : _window_ref(window)
    , _tile_set(tile_set) {
}

void snake::Drawable::setSpritePositionAndScale(sf::Sprite& sprite, const sf::Vector2i& position, const sf::Vector2u& tile_size, const sf::Vector2f scale) {
    sprite.setPosition(static_cast<float>(position.x) * static_cast<float>(tile_size.x) * scale.x, static_cast<float>(position.y) * static_cast<float>(tile_size.y) * scale.y);
}

sf::RenderWindow &snake::Drawable::getWindowRef()
{
    return _window_ref;
}

snake::TileSet& snake::Drawable::getTileSetRef() {
    return _tile_set;
}

snake::DrawSnake::DrawSnake(sf::RenderWindow& window, snake::TileSet& tile_set, const snake::Snake& snake_ref,
              std::map<TypeOfSnakeBodyTileset, sf::Vector2u>& pos_to_tiles) 
    : Drawable(window, tile_set)
    , _snake_ref(snake_ref)
    , _position_to_tiles(std::move(pos_to_tiles)) {
}

void snake::DrawSnake::Draw() {
    // костыльная проверка на часть тела (0 -> голова, [1,snake.size()] - 1 -> тело, оставшееся -> хвост)
    size_t snake_i = 0;

    for (auto it = _snake_ref.cbegin(); it != _snake_ref.cend(); ++it) {
        if (snake_i == 0) {
            // для головы
            auto _sprite = getTileSetRef().getSprite(choiseSnakeHead(it->_direction));
            setSpritePositionAndScale(_sprite, it->_position, getTileSetRef().getTileSize(), getTileSetRef().getScale());
            getWindowRef().draw(_sprite);
        } else if (snake_i + 1 == _snake_ref.getSize()) {
            // для хвоста
            auto _sprite = getTileSetRef().getSprite(choiseSnakeTail(std::prev(it)->_direction));
            setSpritePositionAndScale(_sprite, it->_position, getTileSetRef().getTileSize(), getTileSetRef().getScale());
            getWindowRef().draw(_sprite);
        } else {
            // для тела
            auto _sprite = getTileSetRef().getSprite(choiceSnakeBodyTileset(it));
            setSpritePositionAndScale(_sprite, it->_position, getTileSetRef().getTileSize(), getTileSetRef().getScale());
            getWindowRef().draw(_sprite);
        }
        ++snake_i;
    }
}

sf::Vector2u snake::DrawSnake::choiceSnakeBodyTileset(std::list<snake::Body>::const_iterator it) const {
    auto it_prev = std::prev(it);
    // танцы с бубном
    if (isHorizontalDirection(it_prev->_direction) && isHorizontalDirection(it->_direction)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::HORIZONTAL_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::HORIZONTAL_BODY);
        }
    } else if (isVerticalDirection(it_prev->_direction) && isVerticalDirection(it->_direction)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::VERTICAL_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::VERTICAL_BODY);
        }
    } else if ((it_prev->_direction == Direction::UP && it->_direction == Direction::LEFT) || (it_prev->_direction == Direction::RIGHT && it->_direction == Direction::DOWN)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::L_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::L_BODY);
        }
    } else if ((it_prev->_direction == Direction::UP && it->_direction == Direction::RIGHT) || (it_prev->_direction == Direction::LEFT && it->_direction == Direction::DOWN)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::INVERSE_L_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::INVERSE_L_BODY);
        }
    } else if ((it_prev->_direction == Direction::DOWN && it->_direction == Direction::LEFT) || (it_prev->_direction == Direction::RIGHT && it->_direction == Direction::UP)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::RUSSIAN_G_LETTER_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::RUSSIAN_G_LETTER_BODY);
        }
    } else if ((it_prev->_direction == Direction::DOWN && it->_direction == Direction::RIGHT) || (it_prev->_direction == Direction::LEFT && it->_direction == Direction::UP)) {
        if (_position_to_tiles.find(snake::TypeOfSnakeBodyTileset::INVERSE_RUSSIAN_G_LETTER_BODY) != _position_to_tiles.end()) {
            return _position_to_tiles.at(snake::TypeOfSnakeBodyTileset::INVERSE_RUSSIAN_G_LETTER_BODY);
        }
    } else {
        return {0,0};
    }
    return {0,0};
}

sf::Vector2u snake::DrawSnake::choiseSnakeHead(snake::Direction dir) const {
    sf::Vector2u result = {0,0};
    switch (dir) {
        case snake::Direction::UP    : 
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::HEAD_UP) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::HEAD_UP);
            }
            break;
        case snake::Direction::DOWN  : 
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::HEAD_DOWN) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::HEAD_DOWN);
            }
            break;
        case snake::Direction::LEFT  :
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::HEAD_LEFT) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::HEAD_LEFT);
            }
            break;
        case snake::Direction::RIGHT :
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::HEAD_RIGHT) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::HEAD_RIGHT);
            }
            break;
    }
    return result;
}

sf::Vector2u snake::DrawSnake::choiseSnakeTail(snake::Direction dir) const {
    sf::Vector2u result = {0,0};
    switch (dir) {
        case snake::Direction::UP    : 
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::TAIL_UP) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::TAIL_UP);
            }
            break;
        case snake::Direction::DOWN  : 
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::TAIL_DOWN) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::TAIL_DOWN);
            }
            break;
        case snake::Direction::LEFT  :
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::TAIL_LEFT) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::TAIL_LEFT);
            }
            break;
        case snake::Direction::RIGHT :
            if (_position_to_tiles.find(TypeOfSnakeBodyTileset::TAIL_RIGHT) != _position_to_tiles.end()) {
                result = _position_to_tiles.at(TypeOfSnakeBodyTileset::TAIL_RIGHT);
            }
            break;
    }
    return result;
}

bool snake::DrawSnake::isHorizontalDirection(Direction dir) {
    return dir == Direction::LEFT || dir == Direction::RIGHT;
}

bool snake::DrawSnake::isVerticalDirection(Direction dir) {
    return dir == Direction::UP || dir == Direction::DOWN;
}

snake::DrawMap::DrawMap(sf::RenderWindow &window, snake::TileSet& tile_set, const snake::Map &map_ref, std::vector<sf::Vector2u>& pos_to_tiles)
    : Drawable(window, tile_set)
    , _map_ref(map_ref)
    , _pos_to_tiles(std::move(pos_to_tiles)) {
}

void snake::DrawMap::Draw() {
    for (size_t y = 0; y < _map_ref.getSizeOfMap().y; ++y) {
        for (size_t x = 0; x < _map_ref.getSizeOfMap().x; ++x) {
            auto _sprite = getTileSetRef().getSprite(_pos_to_tiles[static_cast<size_t>(_map_ref.at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}))]);
            setSpritePositionAndScale(_sprite, {static_cast<int>(x), static_cast<int>(y)}, getTileSetRef().getTileSize(), getTileSetRef().getScale());
            getWindowRef().draw(_sprite);
        }
    }
}

snake::DrawEat::DrawEat(sf::RenderWindow &window, snake::TileSet &tile_set, snake::Eat &eat, std::vector<sf::Vector2u>& pos_to_tiles) 
    : Drawable(window, tile_set) 
    , _eat_ref(eat)
    , _pos_to_tiles(std::move(pos_to_tiles)){
}

void snake::DrawEat::Draw() {
    auto _sprite = getTileSetRef().getSprite(_pos_to_tiles[0]);
    setSpritePositionAndScale(_sprite, _eat_ref._coordinate, getTileSetRef().getTileSize(), getTileSetRef().getScale());
    getWindowRef().draw(_sprite);
}
