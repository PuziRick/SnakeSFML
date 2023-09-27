#pragma once

#include <vector>

#include "button.h"
#include "map.h"

namespace snake {

constexpr std::vector<Button> creatDefaultButtons();

class Menu {
public:
    
private:
    std::vector<Button> _buttons; // перечислены все кнопки
    Map _background;              // удобно использовать класс Map для составления случайного заднего фона
};

} // конец namespace snake