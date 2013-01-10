#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include "core/color.h"

#include <GL/glut.h>
#include "glm/glm.hpp"
#include <vector>

struct WorldCoordinate {
   WorldCoordinate(double _x=0.0, double _y=0.0, double _z=0.0)
         : x(_x), y(_y), z(_z) {}
   double x;
   double y;
   double z;
   glm::vec3 normal;
};

// Measured from the bottom left.
typedef WorldCoordinate WindowCoordinate;

// Representation of the bounds in window coordinates.
struct BoundingBox2D {
   BoundingBox2D() {}
   BoundingBox2D(const WindowCoordinate& _min, const WindowCoordinate& _max)
         : min(_min),
           max(_max) {}
   const WindowCoordinate min;
   const WindowCoordinate max;
};

struct BarycentricCoordinate {
   BarycentricCoordinate(const BarycentricCoordinate& other)
         : alpha(other.alpha),
           beta(other.beta),
           gamma(other.gamma) {}
   BarycentricCoordinate(double _beta, double _gamma)
         : alpha(1.0 - _beta - _gamma),
           beta(_beta),
           gamma(_gamma) {}

   const double alpha;
   const double beta;
   const double gamma;

   // Returns true if the coordinate is within bounds (inclusive).
   bool InBounds() const {
      return alpha >= 0.0 && alpha <= 1.0 &&
             beta >= 0.0 && beta <= 1.0 &&
             gamma >= 0.0 && gamma <= 1.0;
   }
};

#endif
