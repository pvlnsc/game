#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "SDL2/SDL.h"

/*
** INTERFACE **
desc:
    Interface that listens for events
*/
class EventListener {
    public:
        virtual void listen(SDL_Event &e) = 0;
};


#endif // EVENT_LISTENER_H