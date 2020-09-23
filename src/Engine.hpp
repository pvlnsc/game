#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "KeyboardEventListener.hpp"
#include "EventListener.hpp"
#include "Background.hpp"
#include "IDrawable.hpp"
#include "IMovable.hpp"
#include "SoundManager.hpp"
#include "Image.hpp"
#include "Text.hpp"

class Engine
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    const int FPS = 60;
    std::vector<std::shared_ptr<EventListener>> listeners;
    std::vector<std::shared_ptr<IDrawable>> drawables;
    std::vector<std::shared_ptr<IMovable>> movables;
    std::shared_ptr<SoundManager> soundManager;
    int startTime = 0;
    bool game_over = false;

    int rangeRandomAlg(int min, int max);
    void handleStateEvents(std::vector<std::shared_ptr<Enemy>> enemies, std::shared_ptr<Player> player, int &enemyKilled);
    void deleteEnemy(std::vector<std::shared_ptr<Enemy>> enemies);
    void drawTextOnScreen(std::stringstream &ss, int &enemyKillCounter, SDL_Renderer *renderer);

    int numOfEnemies = 0;

public:
    Engine(std::string windowTitle, int windowWidth = 1920, int windowHeight = 1080);
    void loop();

    ~Engine();
};

#endif // ENGINE_H