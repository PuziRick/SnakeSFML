#include <SFML/Graphics.hpp>

#include "settings.h"
#include "engine.h"

int main() {
    auto settings = snake::settings::LoaderSettings();
    snake::Engine engine(settings);
    engine.start();
}