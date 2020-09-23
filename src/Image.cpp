#include "Image.hpp"


Image::Image(SDL_Renderer *renderer, std::string imagePath, int posX, int posY)
    : IDrawable(){

        SDL_Surface *surface = IMG_Load(imagePath.c_str());
        rect = new SDL_Rect;
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        rect->x = posX;
        rect->y = posY;

        SDL_QueryTexture(texture, NULL, NULL, &(*rect).w, &(*rect).h);
        
    }

Image::~Image(){
    SDL_DestroyTexture(texture);
    delete rect;
}

void Image::draw(SDL_Renderer *renderer){
    if(present){
        SDL_RenderCopy(renderer, texture, NULL, rect);
    }
}


void Image::setPresent(bool val){ this->present = val; }
bool Image::getPresent(){ return this->present; }