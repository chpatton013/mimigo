#ifndef _SDL_EVENT_LOOP_H_
#define _SDL_EVENT_LOOP_H_

#include "../core/event_loop.h"

class SDLEventLoop : public EventLoop {
  public:
   virtual void RunGame(Game* game, GraphicsAdapter* graphics);
   virtual void Quit();

   virtual void StartNewTimer(Timer::Delegate* delegate,
                              const std::string& event_name,
                              double seconds);

};

#endif
