#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// testing
#include "Rect.hpp"


typedef std::vector<std::shared_ptr<Rect>> Rects;
class SpriteSheet {
    private:
        SDL_Texture *texture {nullptr};    
        std::map<std::string, Rects> animations;
        //std::vector<std::string> animationNames; // for dealloacting, TODO find better way
    public:
        SpriteSheet(std::istream &is, SDL_Renderer *renderer, int numberOfAnimations);
        ~SpriteSheet();
        void drawRect(SDL_Renderer *renderer, std::string animationName, int frame, SDL_Rect *destRect);
        void drawFlippedRect(SDL_Renderer *renderer, std::string animationName, int frame, SDL_Rect *destRect, SDL_RendererFlip flip);
        SDL_Texture* getTexture();
        std::map<std::string, Rects> getAnimations();
        


};


#endif // SPRITESHEET_H