#include "sdl_graphics_adapter.h"
#include <GL/gl.h>

void SDLGraphicsAdapter::Begin() {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //Start our shader
   glUseProgram(g_shader_program);

   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
   glEnable(GL_LINE_SMOOTH);
   /* only set the projection and view matrix once */
   SetProjectionMatrix();
}

void SDLGraphicsAdapter::End() {
}

void SDLGraphicsAdapter::Initialize() {
   display_ = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
   if (!display_) {
      fprintf(stderr, "failed to load sdl display");
      exit(1);
   }
}

void SDLGraphicsAdapter::Draw() {
}
