#ifndef TILESET_H
#define TILESET_H


#include <map>
#include <memory>
#include "Rect.hpp"
#include <fstream>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Tileset {
    private:
        std::map<char, std::shared_ptr<Rect>> tileset;
        SDL_Texture *texture;
        SDL_Rect *destRect;

    public:
        Tileset(std::istream &is, SDL_Renderer *renderer);
        void draw(char code, int x, int y, SDL_Renderer *renderer);
        ~Tileset();
};


#endif // TILESET_H