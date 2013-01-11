LIBS = -lGL -lGLU -lglut -lSDL -I.
HEADERS = core/*.h
GAMEOBJS = sdl/sdl_graphics_adapter.o global/handles.o gl/gl_shader.o gl/GLSL_helper.o
CPPFLAGS= -DGL_GLEXT_PROTOTYPES

all: compile
	mimigo

compile: $(HEADERS) $(GAMEOBJS)
	g++ $(CPPFLAGS) -Wall -Wextra main.cc $(GAMEOBJS) -o mimigo $(LIBS)

clean:
	rm *.o
