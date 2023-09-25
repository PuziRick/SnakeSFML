#include "settings.h"
#include <unordered_map>

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

snake::settings::EatSettings::EatSettings(TileSetSettings tile_set, std::vector<sf::Vector2u> &pos_to_tile)
    : _tiles(tile_set)
    , _pos_to_tiles(std::move(pos_to_tile)) {
}


snake::settings::GameSettings::GameSettings(SnakeSettings snake_conf, MapSettings map_conf, WindowSettings window_conf, EatSettings eat_conf, GAME_SPEED game_speed)
    : _snake_conf(snake_conf)
    , _map_conf(map_conf)
    , _window_conf(window_conf)
    , _eat_conf(eat_conf)
    , _game_speed(game_speed) {
}

// позаимствовал у сообщества
// https://stackoverflow.com/questions/7163069/c-string-to-enum
snake::TypeOfSnakeBodyTileset snake::settings::convertStringToTypeOfSnake(const std::string &type_str) {
    static std::unordered_map<std::string, snake::TypeOfSnakeBodyTileset> converter = {
        {"HEAD_UP", snake::TypeOfSnakeBodyTileset::HEAD_UP} ,
        {"HEAD_DOWN", snake::TypeOfSnakeBodyTileset::HEAD_DOWN} ,
        {"HEAD_LEFT", snake::TypeOfSnakeBodyTileset::HEAD_LEFT} ,
        {"HEAD_RIGHT", snake::TypeOfSnakeBodyTileset::HEAD_RIGHT} ,
        {"TAIL_UP", snake::TypeOfSnakeBodyTileset::TAIL_UP } ,
        {"TAIL_DOWN", snake::TypeOfSnakeBodyTileset::TAIL_DOWN } ,
        {"TAIL_LEFT", snake::TypeOfSnakeBodyTileset::TAIL_LEFT } ,
        {"TAIL_RIGHT", snake::TypeOfSnakeBodyTileset::TAIL_RIGHT } ,
        {"HORIZONTAL_BODY", snake::TypeOfSnakeBodyTileset::HORIZONTAL_BODY } ,
        {"VERTICAL_BODY", snake::TypeOfSnakeBodyTileset::VERTICAL_BODY } ,
        {"RUSSIAN_G_LETTER_BODY", snake::TypeOfSnakeBodyTileset::RUSSIAN_G_LETTER_BODY } ,
        {"INVERSE_RUSSIAN_G_LETTER_BODY", snake::TypeOfSnakeBodyTileset::INVERSE_RUSSIAN_G_LETTER_BODY } ,
        {"L_BODY", snake::TypeOfSnakeBodyTileset::L_BODY } ,
        {"INVERSE_L_BODY", snake::TypeOfSnakeBodyTileset::INVERSE_L_BODY }
    };
    auto it = converter.find(type_str);
    if (it != converter.end()) {
        return it->second;
    } else {
        return snake::TypeOfSnakeBodyTileset::HEAD_UP;
    }
}

snake::settings::GAME_SPEED snake::settings::convertStringToGameSpeed(const std::string &type_str) {
    static std::unordered_map<std::string, snake::settings::GAME_SPEED> converter = {
        {"NORMAL", GAME_SPEED::NORMAL} ,
        {"FAST", GAME_SPEED::FAST} ,
        {"SLOWLY", GAME_SPEED::SLOWLY}
    };
    auto it = converter.find(type_str);
    if (it != converter.end()) {
        return it->second;
    } else {
        return GAME_SPEED::NORMAL;
    }
}

std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> snake::settings::creatSnakeTilesetPos(const snake::ConfigReader &config, const std::string &name) {
    std::vector<std::string> find_value = findValue(name, config);
    std::map<snake::TypeOfSnakeBodyTileset, sf::Vector2u> result;

    for (std::string& value : find_value) {
        std::string tmp = name;
        tmp += ".";
        tmp += value;
        result[convertStringToTypeOfSnake(value)] = findVector2u(tmp, config);
    }
    return result;
}

std::vector<sf::Vector2u> snake::settings::creatPosOfTiles(const snake::ConfigReader &config, const std::string &name) {
    std::vector<std::string> find_value = findValue(name, config);
    std::vector<sf::Vector2u> result;
    result.reserve(find_value.size());
    for (std::string& value : find_value) {
        std::string tmp = name;
        tmp += ".";
        tmp += value;
        result.push_back(findVector2u(tmp, config));
    }
    return result;
}

snake::settings::GameSettings snake::settings::LoaderSettings(const snake::ConfigReader &config) {
    // настройки экрана
    sf::Vector2u WIDESCREEN = findVector2u("WINDOWS_WIDSCREEN", config);
    std::string WINDOW_NAME = findString("WINDOWS_NAME", config);

    // настройки змейки
    std::string SNAKE_IMAGE_NAME = findString("SNAKE_TILESET_NAME", config);
    sf::Vector2u SNAKE_TILES_SIZE = findVector2u("SNAKE_TILE_SIZE", config);
    float SNAKE_SCALE = findFloat("SNAKE_SCALE", config);
    auto SNAKE_POS_TILES(std::move(creatSnakeTilesetPos(config, "SNAKE_POS_TILES")));
    sf::Vector2i SNAKE_START_POS = findVector2i("SNAKE_START_POSITION", config);
    size_t SNAKE_START_SIZE = static_cast<size_t>(findInt("SNAKE_START_SIZE", config));

    // настройки карты
    std::string MAP_IMAGE_NAME = findString("MAP_TILESET_NAME", config);
    sf::Vector2u MAP_TILE_SIZE = findVector2u("MAP_TILE_SIZE", config);
    const sf::Vector2u MAP_SIZE = findVector2u("MAP_SIZE", config);
    float MAP_SCALE = findFloat("MAP_SCALE", config);
    std::vector<sf::Vector2u> MAP_POS_TILES = creatPosOfTiles(config, "MAP_POS_TILES");
    size_t MAP_NUM_OF_TEXTURES = MAP_POS_TILES.size();

    // настройки еды
    std::string EAT_IMAGE_NAME = findString("EAT_IMAGE_NAME", config);
    sf::Vector2u EAT_TILE_SIZE = findVector2u("EAT_TILE_SIZE", config);
    float EAT_SCALE = findFloat("EAT_SCALE", config);
    std::vector<sf::Vector2u> EAT_POS_TILES = creatPosOfTiles(config, "EAT_POS_TILES");
    
    // скорость игры
    GAME_SPEED game_speed = convertStringToGameSpeed(findString("GAME_SPEED", config));
    
    WindowSettings window_conf(WIDESCREEN, WINDOW_NAME);

    TileSetSettings snake_tileset(SNAKE_IMAGE_NAME, SNAKE_TILES_SIZE, SNAKE_SCALE);
    SnakeSettings snake_conf(snake_tileset, SNAKE_POS_TILES, SNAKE_START_POS, SNAKE_START_SIZE);

    TileSetSettings map_tileset(MAP_IMAGE_NAME, MAP_TILE_SIZE, MAP_SCALE);
    MapSettings map_conf(map_tileset, MAP_POS_TILES, MAP_SIZE, MAP_NUM_OF_TEXTURES);

    TileSetSettings eat_tileset(EAT_IMAGE_NAME, EAT_TILE_SIZE, EAT_SCALE);
    EatSettings eat_conf(eat_tileset, EAT_POS_TILES);

    return GameSettings(snake_conf, map_conf, window_conf, eat_conf, game_speed);
}