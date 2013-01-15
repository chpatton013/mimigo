#include "sdl_event_loop.h"
#include "sdl_graphics_adapter.h"
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

void SDLEventLoop::Quit() { exit(0); }

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
   game_ = game;

   const double frames_per_second = 60.0;
   const double updates_per_second = 25.0;

   graphics_ = (SDLGraphicsAdapter*)graphics;

   //StartNewTimer(this, "draw", 1.0/frames_per_second);
   unsigned int last_time = SDL_GetTicks();
   while (true) {
      if (SDL_GetTicks() - last_time >= milli(1.0/updates_per_second)) {
         game_->Update();
         SDL_Event event;
         while(SDL_PollEvent(&event)) {
            switch (event.type) {
               case SDL_KEYDOWN:
                  KeyDown(event);
                  break;
               case SDL_KEYUP:
                  KeyUp(event);
                  break;
               case SDL_QUIT:
                  Quit();
                  break;
            }
         }
         last_time = SDL_GetTicks();
         graphics_->Draw();
      }
   }
}

void SDLEventLoop::KeyUp(SDL_Event &event) {
   switch (event.key.keysym.sym) {
      case SDLK_LEFT:
      case SDLK_a:
         OnLeftButtonUp();
         break;
      case SDLK_RIGHT:
      case SDLK_d:
         OnRightButtonUp();
         break;
      case SDLK_UP:
      case SDLK_w:
         OnUpButtonUp();
         break;
      case SDLK_DOWN:
      case SDLK_s:
         OnDownButtonUp();
         break;
      case SDLK_SPACE:
         OnJumpButtonUp();
         break;
      default:
         break;
   }
}

void SDLEventLoop::KeyDown(SDL_Event &event) {
   switch (event.key.keysym.sym) {
      case SDLK_LEFT:
      case SDLK_a:
         OnLeftButtonDown();
         break;
      case SDLK_RIGHT:
      case SDLK_d:
         OnRightButtonDown();
         break;
      case SDLK_UP:
      case SDLK_w:
         OnUpButtonDown();
         break;
      case SDLK_DOWN:
      case SDLK_s:
         OnDownButtonDown();
         break;
      case SDLK_SPACE:
         OnJumpButtonDown();
         break;
      default:
         break;
   }
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
   graphics_->Draw();
}