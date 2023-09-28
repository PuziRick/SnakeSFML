#include "menu.h"

std::vector<snake::Button> snake::creatDefaultButtons() {
    std::vector<Button> buttons = {
        Button(L"cтарт") ,
        Button(L"Настройки") ,
        Button(L"Выйти")
    };
    return buttons;
}

snake::Menu::Menu(sf::RenderWindow& window, ConfigReader &config)
    : _buttons(std::move(creatDefaultButtons()))
    , _background {
}

