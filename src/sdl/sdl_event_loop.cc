#include "sdl_event_loop.h"
#include "SDL/SDL.h"

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
   SDL_AddTimer(millis, c_timer, &id_);
}

void SDLEventLoop::Quit() {
}

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
}

void SDLEventLoop::StartNewTimer(Timer::Delegate* delegate,
                                 const std::string& event_name,
                                 double seconds) {
}

void SDLEventLoop::ExpireTimer(int id) {
}
