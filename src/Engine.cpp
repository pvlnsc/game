#include "Engine.hpp"

Engine::Engine(std::string windowTitle, int windowWidth, int windowHeight)
{

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    soundManager = std::make_shared<SoundManager>();
    // if(!window) throw SDL_GetError();
    // if(!renderer) throw SDL_GetError();
}
Engine::~Engine()
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    renderer = nullptr;
    window = nullptr;
    SDL_Quit();
}

void Engine::loop()
{

    int maxDelay = 1000 / this->FPS;
    int frameStart = 0;
    int frameEnd = 0;
    bool running = true;

    soundManager->playMusic("./assets/sounds/rpg_village02_loop.wav");
    soundManager->insertSound("./assets/sounds/swish.wav", "swish");
    soundManager->insertSound("./assets/sounds/walk.wav", "walk");
    soundManager->insertSound("./assets/sounds/pain.wav", "pain");
    soundManager->insertSound("./assets/sounds/dead.wav", "dead");
    soundManager->insertSound("./assets/sounds/game_over.wav", "game_over");
    soundManager->insertSound("./assets/sounds/monster_roar.wav", "monster_roar");

    SDL_Event event;
    // Initializaiton
    std::ifstream is{"./assets/sheet.txt"};
    auto bg = std::make_shared<Background>("./assets/world/village.png", renderer);
    auto playerSpriteSheet = std::make_shared<SpriteSheet>(is, renderer, 5); // last parameter is number of animations which are stored in sheet.txt
    auto enemySpriteSheet = std::make_shared<SpriteSheet>(is, renderer, 2);
    auto player = std::make_shared<Player>(playerSpriteSheet, 128, 128, bg);

    std::vector<std::shared_ptr<Enemy>> enemies;

    // Generates random number of enemies from 10 to 20
    numOfEnemies = rand() % 10 + 20;
    std::cout << "Number of enemies: " << numOfEnemies << std::endl;
    for (int i = 0; i < numOfEnemies; i++)
    {
        enemies.push_back(std::make_shared<Enemy>(enemySpriteSheet, 128, 128, bg, rangeRandomAlg(2000, 15000)));
    }

    // Counts how many enemies player has killed
    int enemyKillCounter = 0;

    // An image of movement info
    std::shared_ptr<Image> moveInfo = std::make_shared<Image>(renderer, "./assets/world/move.png", 350, 350);

    drawables.push_back(bg);
    drawables.push_back(player);
    drawables.push_back(moveInfo);

    for (auto enemy : enemies)
    {
        enemy->setFrameSkip(4);
        drawables.push_back(enemy);
    }

    movables.push_back(player);

    ;

    listeners.push_back(player);
    player->setFrameSkip(2);

    while (running)
    {

        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {

                for (size_t i = 0; i < listeners.size(); i++)
                {
                    listeners[i]->listen(event);
                    if (event.type == SDL_KEYUP)
                    {

                        if (player->getState() == 3)
                        {
                            player->setState(0);
                            player->setIsMoving(false);
                        }
                        else if (player->getState() == 2)
                        {
                            player->setState(1);
                            player->setIsMoving(false);
                        }
                        else if (player->getState() == 4)
                        {
                            player->setState(4);
                        }
                        else if (player->getQuit())
                        {
                            running = false;
                        }
                        else
                        {
                            player->setState(0);
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
        SDL_RenderClear(renderer);

        for (const auto movable : movables)
        {
            if (player->getIsDead())
            {
                player->setState(10);
                player->setIsMoving(false);
                continue;
            }
            movable->move();
        }

        for (auto enemy : enemies)
        {
            enemy->listenForPlayerMove(player);
        }

        for (const auto drawable : drawables)
        {
            drawable->draw(renderer);
        }

        soundManager->waitForInput(player, enemies);

        if (frameStart / 1000 == 4)
        {
            moveInfo->setPresent(false);
        }

        handleStateEvents(enemies, player, enemyKillCounter);

        std::stringstream ss;
        drawTextOnScreen(ss, enemyKillCounter, renderer);

        SDL_RenderPresent(renderer);

        frameEnd = SDL_GetTicks();
        if (frameEnd - frameStart < maxDelay)
        {
            SDL_Delay(maxDelay - (frameEnd - frameStart));
        }
    }
}

void Engine::handleStateEvents(std::vector<std::shared_ptr<Enemy>> enemies, std::shared_ptr<Player> player, int &enemyKilled)
{

    // If player was hit, it was set to dying state, it's in dying state set it to dead = laying position
    if (player->getState() == 9 && (SDL_GetTicks() / 1000) - startTime >= 1)
    {

        player->setState(10);
        player->setIsDead(true);
        game_over = true;
    }
    for (auto enemy : enemies)
    {

        if (!enemy->getMoving() && (SDL_GetTicks() / 1000) - startTime >= 1)
        {
            enemy->setState(0);
        }

        if (player->checkCollision(enemy->getSpriteRect()))
        {
            // Collision happened
            startTime = SDL_GetTicks() / 1000;

            // If collision is happened and player is not in his attack state, set his state to 9 = dying
            if (player->getState() == 0 || player->getState() == 1 || player->getState() == 2 || player->getState() == 3)
            {
                player->setState(9);
            }

            // If player is in attack position, set enemy state to dead, set moving of enemy to false, and with setState(0) it won't draw it to the screen
            // TODO kad enemy umre, postaviti ga u laying position = dead i da tu ostane
            if (player->getState() == 8)
            {

                enemy->setMoving(false);
                enemy->setSpriteRectX(enemy->getSpriteRectX() + 100);
                enemy->setState(9);
                enemyKilled++;
            }
        }
    }
}

int Engine::rangeRandomAlg(int min, int max)
{
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do
    {
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

/*
** drawTextOnScreen **
desc:
    draws text on screen, ss needs text to be displayed
params:
    ss - stringstream reference, 
    enemyKillCounter - reference to enemyKillCounter, 
    renderer - pointer to render target, 
return: void - 
*/
void Engine::drawTextOnScreen(std::stringstream &ss, int &enemyKillCounter, SDL_Renderer *renderer)
{

    ss << "Game of Throne";
    Text *title = new Text();
    title->draw(renderer, 28, ss, 350, 30, 255, 255, 255);
    delete title;

    ss << "Enemy killed: ";
    Text *enemyKilledText = new Text();
    enemyKilledText->draw(renderer, 28, ss, 50, 100, 255, 255, 255);
    delete enemyKilledText;

    if (enemyKillCounter == numOfEnemies)
    {
        ss << "You're a true warrior!";
        Text *endGameText = new Text();
        endGameText->draw(renderer, 28, ss, 270, 270, 255, 255, 255);
        delete endGameText;
    }

    if (game_over == true)
    {
        ss << "GAME OVER!";
        Text *endGameText = new Text();
        endGameText->draw(renderer, 50, ss, 330, 370, 255, 255, 255);
        delete endGameText;
    }

    ss << enemyKillCounter;

    Text *enemyKilledCC = new Text();
    enemyKilledCC->draw(renderer, 28, ss, 280, 100, 255, 255, 255);
    delete enemyKilledCC;
}