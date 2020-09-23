#ifndef KEYBOARD_EVENT_LISTENER_H
#define KEYBOARD_EVENT_LISTENER_H


#include "SDL2/SDL.h"
#include "EventListener.hpp"

// TODO use keyboard state instead of handling every key independently
class KeyboardEventListener : public EventListener {
    public:
        virtual void listen(SDL_Event &event) override;
        virtual void listenForKeyboardEvent(SDL_KeyboardEvent &event) = 0;

        
};


#endif // KEYBOARD_EVENT_LISTENER_H