
#ifndef GAME_THRONE_H
#define GAME_THRONE_H

#include <memory>
#include <string>
#include "Engine.hpp"

class GameOfThrone
{
private:
    std::string name;
    std::string release;
    std::shared_ptr<Engine> engine;

public:
    GameOfThrone(std::string name = "Game Of Throne", std::string relase = "1");
    ~GameOfThrone() = default;
};

#endif // GAME_THRONE_H