
#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.hpp"
#include "Background.hpp"
#include "Player.hpp"

class Enemy : public Sprite {
    private:
        bool moving = true;
    public:
        Enemy(std::shared_ptr<SpriteSheet> sheet, int width = 128, int height = 128, std::shared_ptr<Background> bg = nullptr, int position = 1000);
        ~Enemy();
        virtual void draw(SDL_Renderer *renderer) override;
        virtual void move(int dX, int dY) override;
        virtual void move() override;
        void listenForPlayerMove(std::shared_ptr<Player> player);
        void setMoving(bool move);
        bool getMoving();
        
};


#endif // ENEMY_H