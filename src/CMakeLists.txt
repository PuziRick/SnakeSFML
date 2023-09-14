# устанавливаем путь к папке сборки
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

add_library(LIB_SNAKE_S STATIC snake.cpp "${PROJECT_SOURCE_DIR}/include/snake.h")
add_library(LIB_TILE_SET_S STATIC tile_set.cpp "${PROJECT_SOURCE_DIR}/include/tile_set.h")
add_library(LIB_MAP_S STATIC map.cpp "${PROJECT_SOURCE_DIR}/include/map.h")
add_library(LIB_DRAW_S STATIC draw.cpp "${PROJECT_SOURCE_DIR}/include/draw.h")
add_library(READER_S STATIC config_reader.cpp "${PROJECT_SOURCE_DIR}/include/config_reader.h")

target_link_libraries(LIB_SNAKE_S sfml-system sfml-window sfml-graphics)
target_link_libraries(LIB_TILE_SET_S sfml-system sfml-window sfml-graphics)
target_link_libraries(LIB_MAP_S sfml-system sfml-window sfml-graphics)
target_link_libraries(LIB_DRAW_S sfml-system sfml-window sfml-graphics)
