#ifndef PLAYER_H
#define PLAYER_H


#include "Sprite.hpp"
#include "KeyboardEventListener.hpp"



class Player : public Sprite, public KeyboardEventListener{
    private:
        bool isMoving;
        float jumpSpeed;
        float jumpApex;
        bool jumping = false;
        int textureWidth;
        bool isDead = false;
        bool quit = false;
    public:
        Player(std::shared_ptr<SpriteSheet> sheet, int width = 128, int height = 128, std::shared_ptr<Background> bg = nullptr);
        ~Player();
        virtual void draw(SDL_Renderer *renderer) override;
        virtual void move(int dX, int dY) override;
        virtual void move() override;
        void jump();
        virtual void listenForKeyboardEvent(SDL_KeyboardEvent &event) override;
        bool checkCollision(SDL_Rect *enemy);

        bool getIsMoving();
        void setIsMoving(bool move);
        bool getIsDead();
        void setIsDead(bool dead);
        bool getQuit();

        

};


#endif // PLAYER_H