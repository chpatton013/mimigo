#include "hud.h"
#include <string.h>
#include "text2D.h"
#include "shader.h"

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <SDL/SDL.h>



using namespace glm;


void HUD::initHud() {
	initText2D( "src/hud/Holstein.tga" );
}

void HUD::drawHud() {
   char text[256];
   sprintf(text,"%.2f sec", (double)(SDL_GetTicks()) / 1000 );
   char text2[256];
   sprintf(text2, "Get to the last planet!");
   printText2D(text, 10, 500, 60);
   printText2D(text2, 10, 10, 30);
}
