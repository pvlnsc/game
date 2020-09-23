#include "Sprite.hpp"


Sprite::Sprite(std::shared_ptr<SpriteSheet> sheet, int width, int height, std::shared_ptr<Background> bg) : IDrawable(), IMovable(), 
    spriteSheet{sheet}, spriteRect(new SDL_Rect), bg {bg} {
        spriteRect->x = 0;
        spriteRect->y = 603;
        spriteRect->w = width;
        spriteRect->h = height;
        initialFrame = 0;
        frameCounter = 0;
        frameSkip = 0;
    }
Sprite::~Sprite(){
    // delete spriteSheet;
    // spriteSheet = nullptr;
    delete spriteRect;
    
}

// void Sprite::draw(SDL_Renderer *renderer){
    // SDL_Rect destRect {200,200, 128, 128};
    // SDL_RenderCopy(renderer, spriteSheet->getTexture(), spriteSheet->getAnimations()["iddle_blinking"][1]->getTile(), spriteRect);
    
    // spriteSheet->drawRect(renderer, "iddle_blinking", initialFrame, &destRect);
    
// }

void Sprite::move(int dX, int dY){
    spriteRect->x += dX;
    spriteRect->y += dY;
}

void Sprite::move(){
    if(state != 0){
        // walking left
        if(state == 2){
            move(-5, 0);
        }
        // walking right
        if(state == 3){
            move(5, 0);
        }
        // jumping
        if(state == 4){
            move(5, 5);
        }
    }
}


// Getters and Setters
int Sprite::getSpriteRectX(){ return this->spriteRect->x; }
int Sprite::getSpriteRectW(){ return this->spriteRect->y; }
int Sprite::getSpriteRectY(){ return this->spriteRect->w; }
int Sprite::getSpriteRectH(){ return this->spriteRect->h; }
int Sprite::getState(){ return this->state; }
void Sprite::setState(int state){ this->state = state; }
SDL_Rect* Sprite::getSpriteRect(){ return this->spriteRect; }
void Sprite::setFrameSkip(int frameSkip){ 
    if(frameSkip < 0) {
        frameSkip = 0;
    }

    this->frameSkip = frameSkip + 1; 
}

// testing
int Sprite::getInitialFrame(){ return this->initialFrame; }
void Sprite::setInitialFrame(int frame){ this->initialFrame = frame; }
void Sprite::setSpriteRectX(int x){ this->spriteRect->x = x; }
void Sprite::setSpriteRectY(int y){ this->spriteRect->y = y; }
std::shared_ptr<Background> Sprite::getBackground(){ return this->bg; }