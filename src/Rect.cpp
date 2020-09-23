#include "Rect.hpp"



Rect::Rect(std::istream &is){
        int x, y, w, h;
        
        tile = new SDL_Rect;
        
        is >> x >> y >> w >> h;
        // std::cout << "x " << x << " y " << y << " w " << w << " h " << h << std::endl;

        tile->x = x;
        tile->y = y;
        tile->w = w;
        tile->h = h;
    }


Rect::Rect(int x, int y, int w, int h){
        tile->x = x;
        tile->y = y;
        tile->w = w;
        tile->h = h;
    }

Rect::~Rect(){
    delete tile;
}





SDL_Rect* Rect::getTile(){ return this->tile; }
int Rect::getTileX(){ return this->tile->x; }
int Rect::getTileY(){ return this->tile->y; }
int Rect::getTileW(){ return this->tile->w; }
int Rect::getTileH(){ return this->tile->h; }