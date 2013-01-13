#ifndef _SDL_GRAPHICS_ADAPTER_H_
#define _SDL_GRAPHICS_ADAPTER_H_

#include <string>
#include <SDL/SDL.h>
#include "../core/graphics_adapter.h"

class Game;

class SDLGraphicsAdapter : public GraphicsAdapter {
  public:
   SDLGraphicsAdapter(int screen_width, int screen_height, Game* game) :
      GraphicsAdapter(screen_width, screen_height),
      game_(game)
   {}

   virtual void Begin();
   virtual void End();

   virtual void Initialize();
   virtual void Draw();

  private:
   void SetProjectionMatrix();
   void TearDownDraw();

   SDL_Surface* display_;
   Game* game_;
};

#endif

