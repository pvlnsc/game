#ifndef SPRITE_H
#define SPRITE_H

#include <fstream>

#include <memory>
#include "SpriteSheet.hpp"
#include "Rect.hpp"
#include "IDrawable.hpp"
#include "IMovable.hpp"
#include "Background.hpp"

class Sprite : public IDrawable, public IMovable {

    protected:
        std::shared_ptr<SpriteSheet> spriteSheet;
        SDL_Rect *spriteRect {nullptr};
        SDL_RendererFlip flip {SDL_FLIP_HORIZONTAL};
        std::shared_ptr<Background> bg;
        int initialFrame;
        int frameCounter;
        int frameSkip;
        int state;
        enum State: int { IDDLE_RIGHT = 0, IDDLE_LEFT = 1, LEFT = 2, RIGHT = 3, JUMP = 4, JUMP_SLASH =5, RUN_LEFT = 6, RUN_RIGHT=7, ATTACK = 8, DYING = 9, DEAD = 10};
        
    public:
        Sprite(std::shared_ptr<SpriteSheet> sheet, int width = 128, int height = 128, std::shared_ptr<Background> bg = nullptr);
        ~Sprite();
        virtual void draw(SDL_Renderer *renderer) = 0;
        virtual void move(int dX, int dY)= 0;
        virtual void move();
        int getSpriteRectX();
        int getSpriteRectY();
        int getSpriteRectW();
        int getSpriteRectH();
        int getInitialFrame();
        void setInitialFrame(int frame);
        int getState();
        void setState(int state);
        void setFrameSkip(int frameSkip);
        void setSpriteRectX(int x);
        void setSpriteRectY(int y);
        SDL_Rect* getSpriteRect();
        std::shared_ptr<Background> getBackground();
};


#endif // SPRITE_H