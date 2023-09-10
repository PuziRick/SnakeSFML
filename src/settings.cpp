#include "settings.h"

snake::settings::WindowSettings::WindowSettings(sf::Vector2u widescreen, std::string name)
    : _widescreen_x(widescreen.x)
    , _widescreen_y(widescreen.y)
    , _window_name(name) {
}

snake::settings::TileSetSettings::TileSetSettings(std::string image_name, sf::Vector2u tile_size, float scale)
    : _image_name(image_name)
    , _tile_size(tile_size)
    , _scale(scale) {
}

snake::settings::SnakeSettings::SnakeSettings(TileSetSettings tile_set, std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> &pos_to_tile, sf::Vector2i pos, size_t size)
    : _started_position(pos)
    , _started_size(size)
    , _tiles(tile_set)
    , _pos_to_tiles(pos_to_tile) {
}

snake::settings::MapSettings::MapSettings(TileSetSettings tile_set, std::vector<sf::Vector2u> &pos_to_tile, sf::Vector2u size_of_map, size_t num_of_textures)
    : _size_of_map(size_of_map)
    , _num_of_textures(num_of_textures)
    , _tiles(tile_set)
    , _pos_to_tiles(std::move(pos_to_tile)) {
}

snake::settings::GameSettings::GameSettings(SnakeSettings snake_conf, MapSettings map_conf, WindowSettings window_conf)
    : _snake_conf(snake_conf)
    , _map_conf(map_conf)
    , _window_conf(window_conf) {
}

snake::settings::GameSettings snake::settings::LoaderSettings()
{
    const sf::Vector2u WIDESCREEN(640,640);
    const std::string WINDOW_NAME = "SnakeGame";

    const sf::Vector2u TILES_SIZE(64,64);
    const float SCALE = 0.5f;

    const std::string SNAKE_IMAGE_NAME = "images/snake.png";
    const sf::Vector2i SNAKE_START_POS(4,4);
    const size_t SNAKE_START_SIZE = 3;

    const std::string MAP_IMAGE_NAME = "images/grass.png";
    std::vector<sf::Vector2u> map_pos_tiles = {{3,0}, {0,0}, {5,0}};
    const sf::Vector2u MAP_SIZE(20,20);
    const int MAP_NUM_OF_TEXTURES = 1;

    std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> snake_pos_tiles = {
        {snake::TypeOfSnakeBodyTileset::HEAD_UP, {0,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_DOWN, {2,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_LEFT, {3,0}},
        {snake::TypeOfSnakeBodyTileset::HEAD_RIGHT, {1,0}},
        {snake::TypeOfSnakeBodyTileset::TAIL_UP, {0,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_DOWN, {2,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_LEFT, {3,1}},
        {snake::TypeOfSnakeBodyTileset::TAIL_RIGHT, {1,1}},
        {snake::TypeOfSnakeBodyTileset::HORIZONTAL_BODY, {1,3}},
        {snake::TypeOfSnakeBodyTileset::VERTICAL_BODY, {0,3}},
        {snake::TypeOfSnakeBodyTileset::RUSSIAN_G_LETTER_BODY, {1,2}},
        {snake::TypeOfSnakeBodyTileset::INVERSE_RUSSIAN_G_LETTER_BODY, {2,2}},
        {snake::TypeOfSnakeBodyTileset::L_BODY, {0,2}},
        {snake::TypeOfSnakeBodyTileset::INVERSE_L_BODY, {3,2}}
    };

    WindowSettings window_conf(WIDESCREEN, WINDOW_NAME);

    TileSetSettings snake_tileset(SNAKE_IMAGE_NAME, TILES_SIZE, SCALE);
    SnakeSettings snake_conf(snake_tileset, snake_pos_tiles, SNAKE_START_POS, SNAKE_START_SIZE);

    TileSetSettings map_tileset(MAP_IMAGE_NAME, TILES_SIZE, SCALE);
    MapSettings map_conf(map_tileset, map_pos_tiles, MAP_SIZE, MAP_NUM_OF_TEXTURES);

    return GameSettings(snake_conf, map_conf, window_conf);
}
