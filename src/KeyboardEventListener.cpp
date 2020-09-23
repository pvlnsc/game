#include "KeyboardEventListener.hpp"


void KeyboardEventListener::listen(SDL_Event &event){
    if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
        listenForKeyboardEvent(event.key);
    }
}