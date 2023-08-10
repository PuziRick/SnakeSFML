# устанавливаем путь к папке сборки
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

add_library(LIB_SNAKE_S STATIC snake.cpp "${PROJECT_SOURCE_DIR}/include/snake.h")
add_library(LIB_TILE_SET_S STATIC tile_set.cpp "${PROJECT_SOURCE_DIR}/include/tile_set.h")

target_link_libraries(LIB_SNAKE_S sfml-system sfml-window sfml-graphics)
target_link_libraries(LIB_TILE_SET_S sfml-system sfml-window sfml-graphics)