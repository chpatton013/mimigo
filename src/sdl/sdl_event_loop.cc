#include "sdl_event_loop.h"

EventLoop* EventLoop::event_loop_ = NULL;

//static
EventLoop* EventLoop::Instance() {
   if (!event_loop_)
      event_loop_ = new SDLEventLoop();
   return event_loop_;
}

void SDLEventLoop::Quit() {
}

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
}

void SDLEventLoop::StartNewTimer(Timer::Delegate* delegate,
                                 const std::string& event_name,
                                 double seconds) {
}
