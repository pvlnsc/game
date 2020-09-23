#include "Text.hpp"


Text::Text(){
        TTF_Init();
        
    }


Text::~Text(){
    delete rect;
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
}

void Text::draw(SDL_Renderer *renderer, int size, std::stringstream &ss, int posX, int posY, Uint8 R, Uint8 G, Uint8 B){
    


    SDL_Color  color {R,G,B, 255};


    
    font = TTF_OpenFont("./assets/font/FiraCode-Regular.ttf", size);
    if(!font){
        printf( "Failed to load font! Error: %s\n", TTF_GetError() );
    }
    
    
    
    

    SDL_Surface *surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_FreeSurface(surface);
    rect = new SDL_Rect;
    rect->x = posX;
    rect->y = posY;
    SDL_QueryTexture(texture, NULL, NULL, &(*rect).w, &(*rect).h);

    SDL_RenderCopy(renderer, texture, NULL, rect);

    ss.str(std::string());
    ss.clear();

}




void Text::setTextRectW(int w){ this->rect->w = w; }
void Text::setTextRectH(int h){ this->rect->h = h; }
void Text::setTextContent(std::string text){ this->text = text; }
// void Text::setTextColor(Uint8 R, Uint8 G, Uint8 B){
//     color.r = R;
//     color.g = G;
//     color.b = B;
// }