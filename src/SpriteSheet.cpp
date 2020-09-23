
#include "SpriteSheet.hpp"


SpriteSheet::SpriteSheet(std::istream &is, SDL_Renderer *renderer, int numberOfAnimations){
    std::string path;
    std::string animation;
    int totalFrames;
    is >> path;

    // std::cout << path << std::endl;

    SDL_Surface *surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    int counter = 0;
    while(counter < numberOfAnimations) {
        is >> animation;
        // std::cout << "Animation name: " << animation << std::endl;
        
        animations[animation] = Rects();

        is >> totalFrames;
        // std::cout << "Total frames: " <<  totalFrames << std::endl;
        for(int i = 0; i < totalFrames; i++) {
            animations[animation].push_back(std::make_shared<Rect>(is));
        }
        counter++;
    }


}
SpriteSheet::~SpriteSheet(){
    SDL_DestroyTexture(texture);
    // for(auto [k,v] : animations){
    //     for(auto animation: k){
    //         delete v;
    //     }
    // }
}



void SpriteSheet::drawRect(SDL_Renderer *renderer, std::string animationName, int frame,  SDL_Rect *destRect){
    SDL_RenderCopy(renderer, texture, animations[animationName][frame]->getTile(), destRect);
}
void SpriteSheet::drawFlippedRect(SDL_Renderer *renderer, std::string animationName, int frame,  SDL_Rect *destRect, SDL_RendererFlip flip){
    SDL_RenderCopyEx(renderer, texture, animations[animationName][frame]->getTile(), destRect,0, NULL, flip);
}

SDL_Texture* SpriteSheet::getTexture(){ return this->texture; }
std::map<std::string, Rects> SpriteSheet::getAnimations(){ return this->animations; }




