#include <unistd.h>
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "core/mesh_load.h"
#include "gl/gl_shader.h"
#include "gl/gl_mesh.h"
#include "sdl/sdl_graphics_adapter.h"
#include "sdl/sdl_event_loop.h"
#include "game/universe.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/mesh_node.h"

void InitializeSDL() {
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
      fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
   atexit(SDL_Quit);

   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   if (!SDL_SetVideoMode(kScreenWidth, kScreenHeight, 0, SDL_OPENGL)) {
      fprintf(stderr, "SDL_SetVideoMode: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }
}

void InitializeGL() {
   glShadeModel(GL_SMOOTH);
   glViewport(0, 0, 400, 400);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40, 1, 0.0001, 1000.0);
   glMatrixMode(GL_MODELVIEW);
}

void InitializeGlew() {
   glewInit();
   if (GLEW_VERSION_2_0) {
   } else {
      fprintf(stderr, "INFO: OpenGL 2.0 not supported. Exit\n");
      exit(EXIT_FAILURE);
   }
}

// All Initialization code Reference: http://content.gpwiki.org/index.php/OpenGL:Codes:Simple_GLSL_example
void Initialize() {
   InitializeSDL();
   InitializeGL();
   InitializeGlew();
}

void Initialize(Universe*) {
   Initialize();
   chdir("shaders");
   new GLShader("main", "vert_shader.glsl", "frag_shader.glsl");
   chdir("..");
}

void LoadResources(Universe*) {
   GLMesh* bunny = LoadMeshFromFile("../meshes/bunny500.m");
   RootNode::Instance()->AddChild(new MeshNode("bunny", bunny));
   RootNode::Instance()->Draw();
}

void StartMainLoop(Universe* universe) {
   GraphicsAdapter* graphics = new SDLGraphicsAdapter(kScreenWidth, kScreenHeight, universe);
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
