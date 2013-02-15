#ifndef _SDL_EVENT_LOOP_H_
#define _SDL_EVENT_LOOP_H_

#include <list>
#include <vector>
#include "../core/event_loop.h"
#include "../core/timer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>

class SDLGraphicsAdapter;

class SDLTimer : public Timer {
  public:
   SDLTimer(Delegate* delegate, const std::string& event_name) :
      Timer(delegate, event_name),
      seconds_(0.0f),
      start_tick_(0)
   {}

   void Start(double seconds);
   bool Update();
  private:
   double seconds_;
   unsigned int start_tick_;
};

class SDLEventLoop : public EventLoop {
  public:
   virtual void RunGame(Game* game, GraphicsAdapter* graphics);
   virtual void Quit();

   virtual void StartNewTimer(Timer::Delegate* delegate,
                              const std::string& event_name,
                              double seconds);
   void ExpireTimer(int index) { index = index; }
   void PostEvent(const std::string& event);

  private:
   void OnKeyDown(SDL_Event &e);
   void OnKeyUp(SDL_Event &e);

   SDLGraphicsAdapter* graphics_;
   Game* game_;
   std::vector<SDLTimer*> timers_;
   std::list<std::string> events_;
};

#endif
