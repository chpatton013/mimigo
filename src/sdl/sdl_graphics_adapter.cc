#include "sdl_graphics_adapter.h"
#include "../global/handles.h"
#include "../../third_party/glm/glm/gtc/matrix_transform.hpp"
#include "../../third_party/glm/glm/gtc/type_ptr.hpp"
#include "../../third_party/sdl/include/SDL_opengl.h"
#include "../gl/GLSL_helper.h"

void SDLGraphicsAdapter::SetProjectionMatrix() {
   const float field_of_view_y = 80.0f;
   const float z_near = 0.1f;
   const float z_far = 100.0f;
   glm::mat4 projection = glm::perspective(field_of_view_y, aspect_ratio(), z_near, z_far);
   safe_glUniformMatrix4fv(g_handles["uProjMatrix"], glm::value_ptr(projection));
}


void SDLGraphicsAdapter::Begin() {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(g_shaders["main"]);

   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
   glEnable(GL_LINE_SMOOTH);
   SetProjectionMatrix();
}

void SDLGraphicsAdapter::End() {
   glUseProgram(0);
   SDL_GL_SwapBuffers();
}

void SDLGraphicsAdapter::TearDownDraw() {
   safe_glDisableVertexAttribArray(g_handles["aPosition"]);
   safe_glDisableVertexAttribArray(g_handles["aNormal"]);
   safe_glDisableVertexAttribArray(g_handles["aTexture"]);
   safe_glDisableVertexAttribArray(g_handles["aAmbient"]);
   safe_glDisableVertexAttribArray(g_handles["aDiffuse"]);
   //safe_glDisableVertexAttribArray(g_handles["aSpecular"]);
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
