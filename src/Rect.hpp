

#ifndef RECT_H
#define RECT_H

#include "fstream"
#include <iostream>
#include "SDL2/SDL.h"


// SDL_Rect Wrapper class
class Rect {
    private:
        SDL_Rect *tile;
    public:
        Rect(int x, int y, int w, int h);
        Rect(std::istream &is);
        ~Rect();
        SDL_Rect* getTile();
        int getTileX();
        int getTileY();
        int getTileW();
        int getTileH();
};



#endif // RECT_H