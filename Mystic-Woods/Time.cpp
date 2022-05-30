#include "Time.h"
#include "CommonFunc.h"
Time::Time()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
}

Time::~Time()
{

}

void Time::start()
{
    is_started = true;
    is_paused =false;
    start_tick = SDL_GetTicks();
}




int Time::getTicks()
{
    if(is_started == true)
    {
        if(is_paused == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

