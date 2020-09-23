#include "Background.hpp"

Background::Background(std::string path, SDL_Renderer *renderer)
    : IDrawable(){

        

        SDL_Surface *surface = IMG_Load(path.c_str());
        bg = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        


        destRect = new SDL_Rect;
        srcRect = new SDL_Rect;

        destRect->x = 0;
        destRect->y = 0;
        destRect->w = 15000;
        destRect->h = 1000;
        

        srcRect->x = 0;
        srcRect->y = 0;
        srcRect->w = 15000;
        srcRect->h = 1500;



    }

void Background::draw(SDL_Renderer *renderer){
    
    SDL_RenderCopy(renderer, bg, srcRect, destRect);
    
}

Background::~Background(){
    delete destRect;
    delete srcRect;
    SDL_DestroyTexture(bg);
}


SDL_Rect* Background::getDestRect(){ return this->destRect; }
SDL_Rect* Background::getSrcRect(){ return this->srcRect; }
SDL_Texture* Background::getTexture(){ return this->bg; }
void Background::setSrcRectX(int x){ this->srcRect->x = x; }
int Background::getSrcRectX(){ return this->srcRect->x; }
void Background::setDestRectX(int x){ this->destRect->x = x; }
int Background::getDestRectX(){ return this->destRect->x; }
int Background::getDestRectW(){ return this->destRect->w; }
int Background::getSrcRectW(){ return this->srcRect->w; }
void Background::setDestRectW(int w){ this->destRect->w = w; }
void Background::setSrcRectW(int w){ this->srcRect->w = w; }