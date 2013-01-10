LIBS = -lGL -lGLU -lglut -lSDL -I.
HEADERS = core/*.h
GAMEOBJS = sdl_graphics_adapter.o

all: compile
	mimigo

compile: $(HEADERS) $(GAMEOBJS)
	g++ -Wall -Wextra main.cc $(GAMEOBJS) -o mimigo $(LIBS)

clean:
	rm *.o
