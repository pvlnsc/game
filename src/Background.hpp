

#ifndef SCROLLING_BG
#define SCROLLING_BG


#include <iostream>
#include <string>

#include "SDL2/SDL_image.h"
#include "IDrawable.hpp"


class Background : public IDrawable {
    private:
        SDL_Texture *bg;
        SDL_Rect *srcRect;
        SDL_Rect *destRect;
        
        
    public:
        Background(std::string path, SDL_Renderer *renderer);
        ~Background();
        void draw(SDL_Renderer *renderer) override;
        

        SDL_Rect *getSrcRect();
        SDL_Rect *getDestRect();
        SDL_Texture *getTexture();
        void setSrcRectX(int x);
        int getSrcRectX();
        void setDestRectX(int x);
        int getDestRectX();
        int getDestRectW();
        int getSrcRectW();
        void setDestRectW(int w);
        void setSrcRectW(int w);

        
        




};  


#endif // SCROLLING_BG