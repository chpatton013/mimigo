#include "hud.h"
#include <string.h>
#include "text2D.h"
#include "shader.h"
#include <SDL/SDL.h>
#include "../global/handles.h"

extern float g_draw_rate;
extern float g_update_rate;

void HUD::initHud() {
	initText2D( "src/hud/Holstein.tga" );
	updateTime = true;
}


void HUD::drawHud() {
   char text[2][256];

   if(updateTime){
   time = SDL_GetTicks() / 1000.0f;
   }
   if (win_mode) {
      sprintf(text[0], "You Win!");
   } else {
      sprintf(text[0], "Run Edgar! Run!");
   }
   sprintf(
      text[1],
      "%.2f sec | %.2f fps | %.2f ups",
      time, g_draw_rate, g_update_rate
   );

   printText2D(text[0], 30, 530, 48);
   printText2D(text[1], 10, 10, 24);
}
