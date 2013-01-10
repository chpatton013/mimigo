#ifndef _COLOR_H_
#define _COLOR_H_

// On a scale of 0-255
struct Color {
   Color(double _r=0.0, double _g=0.0, double _b=0.0, double _f=0.0)
         : r(_r),
           g(_g),
           b(_b) {}

   double r;
   double g;
   double b;
   double f; // filter or alpha
   
   Color operator+(const Color& other) const {
      return Color(r + other.r, g + other.g, b + other.b, f + other.f);
   }

   Color scale(double scale) const {
      return Color(scale * r, scale * g, scale * b, scale * f);
   }
};
typedef Color color_t;

#endif
