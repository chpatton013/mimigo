#include "SDL/SDL.h"
#include "sdl_graphics_adapter.h"

void InitializeSDL() {
   // Load SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }
}

void Initialize() {
   InitializeSDL();
}

void LoadResources() {
}

void StartMainLoop() {
   GraphicsAdapter* graphics = new SDLGraphicsAdapter(1024, 768);
   graphics->Initialize();
}

int main(int , char** ) {

   Initialize();
   LoadResources();
   StartMainLoop();

   return 0;
}
