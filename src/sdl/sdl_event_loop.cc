#include "sdl_event_loop.h"
#include "SDL/SDL.h"
#include <assert.h>

static Uint32 c_timer(Uint32 interval, void *id) {
   EventLoop::Instance()->ExpireTimer(*(int*)id);
}

unsigned int SDLTimer::value_ = 0;
EventLoop* EventLoop::event_loop_ = NULL;

//static
EventLoop* EventLoop::Instance() {
   if (!event_loop_)
      event_loop_ = new SDLEventLoop();
   return event_loop_;
}

void SDLTimer::Start(double seconds) {
   const unsigned int millis = seconds * 1000.0;
   assert(SDL_AddTimer(millis, c_timer, &id_));
}

void SDLEventLoop::Quit() {
}

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
   game_ = game;

   OnExpiration("");
   SDL_Event event;
   while(true) {
      usleep(10000);
   }
}

static inline SDL_Event* makeUpdateEvent() {
   SDL_Event* event = new SDL_Event();
   SDL_UserEvent user_event;
   user_event.type = SDL_USEREVENT;
   user_event.code = 0;
   user_event.data1 = NULL;
   user_event.data2 = NULL;
   event->type = SDL_USEREVENT;
   event->user = user_event;
   return event;
}

void SDLEventLoop::StartNewTimer(Timer::Delegate* delegate,
                                 const std::string& event_name,
                                 double seconds) {
   timers_.push_back(SDLTimer(delegate, event_name));
   timers_.back().Start(seconds);
}

void SDLEventLoop::ExpireTimer(int id) {
   std::vector<SDLTimer>::iterator it;
   for (it = timers_.begin(); it != timers_.end(); ++it) {
      if (it->id_ == id) {
         it->OnExpiration();
         timers_.erase(it);
         return;
      }
   }
}

void SDLEventLoop::OnExpiration(const std::string& event_name) {
   game_->Update();
   StartNewTimer(this, "", 1.0/60.0);
}
