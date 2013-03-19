#ifndef HUD_H
#define HUD_H


class HUD {
   public:
      void initHud();
      void drawHud();
      void setTimeUpdate(){updateTime = false;}
      
      float time;
      bool updateTime;

};

#endif
