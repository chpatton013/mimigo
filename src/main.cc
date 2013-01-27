#include <unistd.h>
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "core/mesh_load.h"
#include "core/camera.h"
#include "gl/gl_shader.h"
#include "gl/gl_mesh.h"
#include "sdl/sdl_graphics_adapter.h"
#include "sdl/sdl_event_loop.h"
#include "game/universe.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/mesh_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include "core/entity_component.h"

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
   glViewport(0, 0, kScreenWidth, kScreenHeight);

   // Start Of User Initialization
   glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
   // Black Background
   glClearDepth (1.0f);    // Depth Buffer Setup
   glDepthFunc (GL_LEQUAL);    // The Type Of Depth Testing
   glEnable (GL_DEPTH_TEST);// Enable Depth Testing
   glVertexPointer(3, GL_FLOAT, 0, 0);
}

void InitializeGlew() {
   glewInit();
   if (!GLEW_VERSION_2_0) {
      fprintf(stderr, "INFO: OpenGL 2.0 not supported. Exit\n");
      exit(EXIT_FAILURE);
   }
}

// All Initialization code Reference: http://content.gpwiki.org/index.php/OpenGL:Codes:Simple_GLSL_example
void Initialize() {
   InitializeSDL();
   InitializeGL();
   InitializeGlew();
   new GLShader("main", "src/shaders/wave.vert", "src/shaders/wave.frag");
}

void LoadResources() {
   EntityComponent* go_gopher = LoadEntityComponentFromOBJ("meshes/go_gopher_push.obj");
   EntityComponentNode* mesh = new EntityComponentNode("bunny", go_gopher);
   mesh->apply_transformation(glm::scale(glm::mat4(), glm::vec3(0.2f)));

   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/sphere.obj");

   RootNode::Instance()->AddChild(mesh);
   RootNode::Instance()->AddChild(new EntityComponentNode("planet1", sphere));
   RootNode::Instance()->AddChild(new EntityComponentNode("planet2", sphere));
   RootNode::Instance()->AddChild(new EntityComponentNode("planet3", sphere));
   RootNode::Instance()->AddChild(new EntityComponentNode("planet4", sphere));
   RootNode::Instance()->AddChild(new EntityComponentNode("planet5", sphere));
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid1", sphere));
   SceneNode::Get("asteroid1")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid2", sphere));
   SceneNode::Get("asteroid2")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid3", sphere));
   SceneNode::Get("asteroid3")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid4", sphere));
   SceneNode::Get("asteroid4")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid5", sphere));
   SceneNode::Get("asteroid5")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid6", sphere));
   SceneNode::Get("asteroid6")->set_visible(false);
   RootNode::Instance()->AddChild(new EntityComponentNode("asteroid7", sphere));
   SceneNode::Get("asteroid7")->set_visible(false);
}

void StartMainLoop(Universe* universe) {
   GraphicsAdapter* graphics = new SDLGraphicsAdapter(kScreenWidth, kScreenHeight, universe);
   graphics->Initialize();
   SDLEventLoop::Instance()->RunGame(universe, graphics);
}

int main(int , char** ) {
   Initialize();
   LoadResources();

   Universe* universe = new Universe();
   StartMainLoop(universe);

   return 0;
}
