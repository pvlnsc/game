#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "SDL2/SDL.h"

class IDrawable {
    public:
        virtual void draw(SDL_Renderer *renderer) = 0;
        virtual ~IDrawable() = default;


};


#endif // IDRAWABLE_H 