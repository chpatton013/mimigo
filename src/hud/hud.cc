#include "hud.h"
#include <string.h>
#include "text2D.h"
#include "shader.h"
#include <SDL/SDL.h>

extern float g_draw_rate;
extern float g_update_rate;

void HUD::initHud() {
	initText2D( "src/hud/Holstein.tga" );
}

void HUD::drawHud() {
   char text[2][256];
   sprintf(text[0], "Run Edgar! Run!");
   sprintf(
      text[1],
      "%.2f sec | %.2f fps | %.2f ups",
      SDL_GetTicks() / 1000.0f, g_draw_rate, g_update_rate
   );

   printText2D(text[0], 30, 530, 48);
   printText2D(text[1], 10, 10, 24);
}
