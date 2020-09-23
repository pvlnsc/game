#ifndef IMAGE_LOAD_H
#define IMAGE_LOAD_H


#include <string>

#include "IDrawable.hpp"
#include "SDL2/SDL_image.h"

class Image : public IDrawable {
    private:
        SDL_Rect *rect;
        SDL_Texture *texture;
        bool present = true;

    public:
        Image(SDL_Renderer *renderer, std::string imagePath, int posX, int posY);
        ~Image();
        virtual void draw(SDL_Renderer *renderer);
        void setPresent(bool val);
        bool getPresent();
};


#endif // IMAGE_LOAD_H