#ifndef _SDL_EVENT_LOOP_H_
#define _SDL_EVENT_LOOP_H_

#include <vector>
#include "../core/event_loop.h"
#include "../core/timer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>

class SDLGraphicsAdapter;

class SDLEventLoop : public EventLoop {
  public:
   virtual void RunGame(Game* game, GraphicsAdapter* graphics);
   virtual void Quit();

   virtual void StartNewTimer(Timer::Delegate* delegate,
                              const std::string& event_name,
                              double seconds) {assert(false);}
   void ExpireTimer(int id) {assert(false);}

  private:
   void OnKeyDown(SDL_Event &e);
   void OnKeyUp(SDL_Event &e);

   SDLGraphicsAdapter* graphics_;
   Game* game_;
};

#endif
