#include "Tileset.hpp"


Tileset::Tileset(std::istream &is, SDL_Renderer *renderer){

    std::string path;
    is >> path;

    SDL_Surface *surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);
    while(!is.eof()){
        char code;
        is >> code;
        tileset[code] = std::make_shared<Rect>(is);
    }

    destRect = new SDL_Rect;

}

void Tileset::draw(char code, int x, int y, SDL_Renderer *renderer){
    destRect->x = x;
    destRect->y = y;
    destRect->w = tileset[code]->getTileW();
    destRect->h = tileset[code]->getTileH();
    SDL_RenderCopy(renderer, texture, tileset[code]->getTile(), destRect);
}


Tileset::~Tileset(){
    delete destRect;
}