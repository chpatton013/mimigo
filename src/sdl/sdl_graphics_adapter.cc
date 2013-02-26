#include "sdl_graphics_adapter.h"
#include "../global/handles.h"
#include "../gl/GLSL_helper.h"
#include "../gl/gl_shader.h"
#include "../core/game.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void SDLGraphicsAdapter::SetProjectionMatrix() {
   const float field_of_view_y = 80.0f;
   const float z_near = 0.1f;
   const float z_far = 1000.0f;
   projection = glm::perspective(field_of_view_y, aspect_ratio(), z_near, z_far);
   safe_glUniformMatrix4fv(g_handles["uProjMatrix"], glm::value_ptr(projection));
}


void SDLGraphicsAdapter::Begin() {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(g_shaders["main"]);

   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
   glEnable(GL_LINE_SMOOTH);
   SetProjectionMatrix();

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_INDEX_ARRAY);
}

void SDLGraphicsAdapter::End() {
   glUseProgram(0);
   SDL_GL_SwapBuffers();
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_INDEX_ARRAY);
}

void SDLGraphicsAdapter::TearDownDraw() {
   safe_glDisableVertexAttribArray(g_handles["aPosition"]);
   safe_glDisableVertexAttribArray(g_handles["aNormal"]);
   safe_glDisableVertexAttribArray(g_handles["aTexture"]);
   safe_glDisableVertexAttribArray(g_handles["aAmbient"]);
   safe_glDisableVertexAttribArray(g_handles["aDiffuse"]);
   safe_glDisableVertexAttribArray(g_handles["aSpecular"]);
}

void SDLGraphicsAdapter::Initialize() {
}

void SDLGraphicsAdapter::Draw() {
   Begin();
   game_->Draw();
   End();
}
