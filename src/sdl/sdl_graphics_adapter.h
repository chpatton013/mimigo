#ifndef _SDL_GRAPHICS_ADAPTER_H_
#define _SDL_GRAPHICS_ADAPTER_H_

#include <string>
#include <SDL/SDL.h>
#include "../core/graphics_adapter.h"

class SDLGraphicsAdapter : public GraphicsAdapter {
  public:
   SDLGraphicsAdapter(int screen_width, int screen_height) :
      GraphicsAdapter(screen_width, screen_height)
   {}

   virtual void Begin();
   virtual void End();

   virtual void Initialize();
   virtual void Draw();

  private:
   void SetProjectionMatrix();
   void TearDownDraw();

   SDL_Surface* display_;
};

#endif

