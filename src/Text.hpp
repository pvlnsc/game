#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <iostream>
#include <sstream>

#include "SDL2/SDL_ttf.h"



class Text {

    private:
        SDL_Texture *texture {nullptr};
        TTF_Font *font {nullptr};
        
        std::string text;
        SDL_Rect *rect;
        
    public:
        Text();
        ~Text();
        void draw(SDL_Renderer *renderer, int size, std::stringstream &ss, int posX, int posY, Uint8 R, Uint8 G, Uint8 B);
        void setTextRectW(int w);
        void setTextRectH(int h);
        void setTextContent(std::string text);
        void setTextColor(Uint8 R, Uint8 G, Uint8 B);
        


};


#endif // TEXT_H