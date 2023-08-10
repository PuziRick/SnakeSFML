# ===================================================================
#                       Информация о проекте
# ===================================================================

cmake_minimum_required(VERSION 3.20)

# Устанавливаем название проекта/исполняемого файла и версию С++
set(PROJECT_NAME snake)
set(CMAKE_CXX_STANDARD 17)

# Определяем проект
project(${PROJECT_NAME})
option(BUILD_TESTS "Включить модульное тестирование" ON)
option(BUILD_LIBS "Включить сборку библиотек" ON)

# ===================================================================
#                       Настройка компилятора
# ===================================================================

# Устанавливает флаги компиляции и запрещаем расширения языка
# отдельное спасибо https://habr.com/ru/articles/461817/
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# ===================================================================
#                Компиляция исполняемого файла игры
# ===================================================================

# Установка исходных и заголовочных файлов
file(GLOB SOURCE "${PROJECT_SOURCE_DIR}/src/*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/include")

# Указываем путь к собранной и установленной SFML
set(SFML_DIR "D:/SFML")

# Добавляем путь к SFML в список префиксов
list(APPEND CMAKE_PREFIX_PATH "${SFML_DIR}")

# Умоляем собрать исполняемый файл со статической библиотекой SFML
set(SFML_STATIC_LIBRARIES TRUE)

# Вычисляем по IP и добавляем SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCE})

# Линкуем библиотеку SFML к исполняяему файлу игры
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

# ===================================================================
#                       Компиляция библиотек
# ===================================================================

if(NOT BUILD_LIBS)
    message(STATUS "Сборка библиотек выключена")
else()
    add_subdirectory(src)
endif()

# ===================================================================
#                               Тесты
# ===================================================================

# костыль тестирование не будет работать если не собрать библиотеки
if((NOT BUILD_TESTS) OR (NOT BUILD_LIBS))
    message(STATUS "Тестирование проекта выключено")
else()
    add_subdirectory(tests)
endif()

#add_library(SNAKE_LIB src/snake.cpp include/snake.h)
#
#target_link_libraries(SNAKE_LIB sfml-system sfml-window sfml-graphics)
#
#if (BUILD_TESTS)
#    set(TESTS_NAME TestApp)
#    file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")
#    add_executable(${TESTS_NAME} ${TEST_SOURCES})
#
#    set_target_properties(${TESTS_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
#    target_link_libraries(${TESTS_NAME} SNAKE_LIB)
#    target_link_libraries(${TESTS_NAME} sfml-system sfml-window sfml-graphics)
#endif()