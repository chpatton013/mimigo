#ifndef _SDL_EVENT_LOOP_H_
#define _SDL_EVENT_LOOP_H_

#include <vector>
#include "../core/event_loop.h"
#include "../core/timer.h"

class SDLTimer : public Timer {
  public:
   SDLTimer(Delegate* delegate, const std::string& event_name) :
      Timer(delegate, event_name),
      id_(value_++)
   {}

   void Start(double seconds);
   unsigned int id_;
  private:
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
   Game* game_;
   std::vector<SDLTimer> timers_;

};

#endif
