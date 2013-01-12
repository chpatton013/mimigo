LIBS = -lGL -lGLU -lSDL -I./src -I./third_party
HEADERS = core/*.h
GAMEOBJS = sdl/sdl_graphics_adapter.o global/handles.o gl/gl_shader.o gl/GLSL_helper.o sdl/sdl_event_loop.o \
			  core/event_loop_registrar.o game/universe.o scene_hierarchy/scene_node.o \
			  scene_hierarchy/root_node.o util/glm_util.o gl/gl_mesh.o core/mesh_load.o
CPPFLAGS= -DGL_GLEXT_PROTOTYPES

all: compile
	mimigo

compile: $(HEADERS) $(GAMEOBJS)
	g++ $(CPPFLAGS) -Wall -Wextra main.cc $(GAMEOBJS) -o mimigo $(LIBS)

clean:
	rm */*.o
