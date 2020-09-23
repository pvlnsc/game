#include "GameOfThrone.hpp"

GameOfThrone::GameOfThrone(std::string name, std::string release)
    : name{name}, release{release}
{

    engine = std::make_shared<Engine>(name);
    engine->loop();
}
