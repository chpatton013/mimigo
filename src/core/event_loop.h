#ifndef _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

#include <stdio.h>

#include "core/game.h"
#include "core/timer.h"
#include "core/event_observer.h"

class GraphicsAdapter;

// Abstract class representing the event loop that drives the Game.
// Calls Update() 60 times/sec, Draw() 60 times/sec when there are no events
// to be handled. When there is an event to be handled, passes the event to
// the event handler.
class EventLoop : public EventSubject {
  public:
   enum StateType {
      MAIN_MENU_STATE,
      GAME_PLAY_STATE,
      LEVEL_EDITOR_STATE,
      LEVEL_EDITOR_MENU_STATE,
      SAVE_STATE,
      LOAD_STATE,
      QUIT_STATE
   };

   static EventLoop* Instance();
   virtual void RunGame(Game* game, GraphicsAdapter* graphics) = 0;
   virtual void Quit() = 0;
   virtual StateType State() const { return state_; }
   virtual void ChangeState(StateType state)
      { state_ = state; }

   virtual void StartNewTimer(Timer::Delegate* delegate,
                              const std::string& event_name,
                              double seconds) = 0;

  protected:
   EventLoop() : state_(MAIN_MENU_STATE) {}

   virtual ~EventLoop() {}

   void Update(Game* game) { game->Update(); }
   void Draw(GraphicsAdapter& graphics) {assert(0);}

  private:
   StateType state_;
   static EventLoop* event_loop_;
};

#endif
