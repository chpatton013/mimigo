#include "SDL/SDL.h"
#include "gl/gl_shader.h"
#include "sdl/sdl_graphics_adapter.h"
#include "sdl/sdl_event_loop.h"
#include "universe.h"

void InitializeSDL() {
   // Load SDL
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }
}

void Initialize(Universe*) {
   InitializeSDL();
   chdir("shaders");
   new GLShader("main", "vert_shader.glsl", "frag_shader.glsl");
   chdir("..");
}

void LoadResources(Universe*) {
}

void StartMainLoop(Universe* universe) {
   GraphicsAdapter* graphics = new SDLGraphicsAdapter(1024, 768);
   graphics->Initialize();
   SDLEventLoop::Instance()->RunGame(universe, graphics);
}

int main(int , char** ) {

   Universe* universe = new Universe();

   Initialize(universe);
   LoadResources(universe);
   StartMainLoop(universe);

   return 0;
}
