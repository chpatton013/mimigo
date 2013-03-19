#include "sdl_event_loop.h"
#include "sdl_graphics_adapter.h"
#include "SDL/SDL.h"
#include <assert.h>
#include "../global/handles.h"

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
   seconds_ = seconds;
   start_tick_ = SDL_GetTicks();
}

bool SDLTimer::Update() {
   return SDL_GetTicks() - start_tick_ > milli(seconds_);
}

void SDLEventLoop::Quit() { exit(0); }

void SDLEventLoop::RunGame(Game* game, GraphicsAdapter* graphics) {
   game_ = game;

   //const double frames_per_second = 60.0;
   const double updates_per_second = 25.0;

   graphics_ = (SDLGraphicsAdapter*)graphics;

   unsigned int last_update_time = SDL_GetTicks();
   while (true) {
      if (SDL_GetTicks() - last_update_time >= milli(1.0/updates_per_second)) {
         game_->Update();
         SDL_Event event;
         while(SDL_PollEvent(&event)) {
            switch (event.type) {
               case SDL_KEYDOWN:
                  OnKeyDown(event);
                  break;
               case SDL_KEYUP:
                  OnKeyUp(event);
                  break;
               case SDL_QUIT:
                  Quit();
                  break;
            }
         }

         while (!events_.empty()) {
            game_->OnEvent(events_.front());
            events_.pop_front();
         }

         std::vector<SDLTimer*> expired_timers;
         for (unsigned int i = 0; i < timers_.size(); ++i)
            if (timers_[i]->Update())
               expired_timers.push_back(timers_[i]);

         for (unsigned int i = 0; i < expired_timers.size(); ++i) {
            expired_timers[i]->OnExpiration();
            timers_.erase(std::find(timers_.begin(), timers_.end(), expired_timers[i]));
            delete expired_timers[i];
         }

         last_update_time = SDL_GetTicks();
         graphics_->Draw();
      }
   }
}

void SDLEventLoop::StartNewTimer(Timer::Delegate* delegate,
                                 const std::string& event_name,
                                 double seconds) {
   timers_.push_back(new SDLTimer(delegate, event_name));
   timers_.back()->Start(seconds);
}

void SDLEventLoop::PostEvent(const std::string& event) {
   events_.push_back(event);
}

void SDLEventLoop::OnKeyUp(SDL_Event &event) {
   switch (event.key.keysym.sym) {
      case SDLK_LEFT:  case SDLK_a: OnLeftButtonUp();       break;
      case SDLK_RIGHT: case SDLK_d: OnRightButtonUp();      break;
      case SDLK_UP:    case SDLK_w: OnUpButtonUp();         break;
      case SDLK_DOWN:  case SDLK_s: OnDownButtonUp();       break;
      case SDLK_SPACE:              OnJumpButtonUp();       break;
      case SDLK_i:                  OnCameraUpUp();         break;
      case SDLK_k:                  OnCameraDownUp();       break;
      case SDLK_z:                  zoe_mode = !zoe_mode;   break;
      default:                                              break;
   }
}

void SDLEventLoop::OnKeyDown(SDL_Event &event) {
   switch (event.key.keysym.sym) {
      case SDLK_LEFT:  case SDLK_a: OnLeftButtonDown();   break;
      case SDLK_RIGHT: case SDLK_d: OnRightButtonDown();  break;
      case SDLK_UP:    case SDLK_w: OnUpButtonDown();     break;
      case SDLK_DOWN:  case SDLK_s: OnDownButtonDown();   break;
      case SDLK_SPACE:              OnJumpButtonDown();   break;
      case SDLK_i:                  OnCameraUpDown();     break;
      case SDLK_k:                  OnCameraDownDown();   break;
      default:                                            break;
   }
}
