#ifndef _GRAPHICS_ADAPTER_H_
#define _GRAPHICS_ADAPTER_H_

#include <string>

namespace {
const std::string kPNG(".png");
const std::string kBMP(".bmp");
}

class GraphicsAdapter {
  public:
   GraphicsAdapter(int screen_width, int screen_height) :
      screen_width_(screen_width),
      screen_height_(screen_height),
      aspect_ratio_(float(screen_width)/screen_height)
   {}

   virtual void Begin() = 0;
   virtual void End() = 0;

   virtual void Initialize() = 0;
   virtual void Draw() = 0;

  protected:
   float aspect_ratio() { return aspect_ratio_; }
   int screen_width() { return screen_width_; }
   int screen_height() { return screen_height_; }
   void set_screen_width(int screen_width)
      { screen_width_ = screen_width; }
   void set_screen_height(int screen_height)
      { screen_height_ = screen_height; }

  private:
   int screen_width_;
   int screen_height_;
   float aspect_ratio_;
};

#endif
