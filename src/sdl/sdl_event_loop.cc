#include "sdl_event_loop.h"
#include "SDL/SDL.h"
#include <assert.h>

static Uint32 c_timer(Uint32 interval, void *id) {
   SDLEventLoop::Instance()->ExpireTimer(*(int*)id);
   return interval;
}

unsigned int SDLTimer::value_ = 0;
EventLoop* EventLoop::event_loop_ = NULL;

//static
EventLoop* EventLoop::Instance() {
   if (!event_loop_)
      event_loop_ = new SDLEventLoop();
   return event_loop_;
}

inline unsigned int milli(double seconds) {
   return seconds * 1000.0;
}

void SDLTimer::Start(double seconds) {
   timer_id_ = SDL_AddTimer(milli(seconds), c_timer, &id_);
}

void SDLEventLoop::Quit() {
}

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
   game_ = game;

   const double seconds_per_frame = 1.0;
   StartNewTimer(this, "", seconds_per_frame);
   while(true) { }
}

void SDLEventLoop::StartNewTimer(Timer::Delegate* delegate,
                                 const std::string& event_name,
                                 double seconds) {
   timers_.push_back(SDLTimer(delegate, event_name));
   timers_.back().Start(seconds);
}

void SDLEventLoop::ExpireTimer(int id) {
   for (std::vector<SDLTimer>::iterator it = timers_.begin();
         it != timers_.end(); ++it) {
      if (it->id_ == id) {
         it->OnExpiration();
         return;
      }
   }
}

void SDLEventLoop::OnExpiration(const std::string& event_name) {
   game_->Update();
}
