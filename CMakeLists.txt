cmake_minimum_required(VERSION 3.20)

# Устанавливаем название проекта/исполняемого файла и версию С++
set(PROJECT_NAME snake)
set(CMAKE_CXX_STANDARD 17)

# Определяем проект
project(${PROJECT_NAME})

# Установка исходных и заголовочных файлов
set(SOURCE  src/main.cpp
            src/snake.cpp
    )
set(HEADER  include/snake.h)

# Указываем путь к собранной и установленной SFML
set(SFML_DIR "D:/SFML")

# Добавляем путь к SFML в список префиксов
list(APPEND CMAKE_PREFIX_PATH "${SFML_DIR}")

# Умоляем собрать исполняемый файл со статической библиотекой SFML
set(SFML_STATIC_LIBRARIES TRUE)

# Вычисляем по IP и добавляем SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

option(BUILD_TEST "Build tests" OFF)

set(TEST_HEADER test/my_test_framework.h
                test/test_snake.h
)

if (BUILD_TEST)
    include_directories(../include)
    add_executable(test_exe test/test_all.cpp ${HEADERS} ${TEST_HEADER})
    target_link_libraries(test_exe sfml-system sfml-window sfml-graphics)
endif()

# Линкуем хедеры и SFML
include_directories(include)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)