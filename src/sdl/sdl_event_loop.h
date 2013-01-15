#ifndef _SDL_EVENT_LOOP_H_
#define _SDL_EVENT_LOOP_H_

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
      id_(value_++)
   {}

   void Start(double seconds);

   unsigned int id_;
  private:
   SDL_TimerID timer_id_;

   static unsigned int value_;
};

class SDLEventLoop : public EventLoop,
                     public Timer::Delegate {
  public:
   virtual void RunGame(Game* game, GraphicsAdapter* graphics);
   virtual void Quit();

   virtual void StartNewTimer(Timer::Delegate* delegate,
                              const std::string& event_name,
                              double seconds);
   void ExpireTimer(int id);
   virtual void OnExpiration(const std::string& event_name);

  private:
   void KeyDown(SDL_Event &e);
   void KeyUp(SDL_Event &e);

   SDLGraphicsAdapter* graphics_;
   Game* game_;
   std::vector<SDLTimer> timers_;
};

#endif