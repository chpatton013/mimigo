#ifndef _GAME_H_
#define _GAME_H_

#include "event_loop_registrar.h"
#include "event_observer.h"

//TODO: Rename to game_state.
class Game : public EventObserver {
  public:
   Game() { Initialize(); }

   virtual void Update() = 0;
   virtual void Draw() = 0;

   EventLoopRegistrar registrar_;
  private:
   void Initialize() { registrar_.Register(this); }
};

#endif
