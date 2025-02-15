#include "test_snake.h"
#include "test_tileset.h"
#include "test_map.h"
#include "test_config_reader.h"
#include "my_test_framework.h"

int main() {
    RUN_TEST(TestSnake);        // Проверка работы класса Snake
    RUN_TEST(TestTileSet);      // Проверка работы класса TileSet
    RUN_TEST(TestMap);          // Проверка работы класса Map
    RUN_TEST(TestConfigReader); // Проверка работы парсинга данных
}
