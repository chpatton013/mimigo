#ifndef _ROTATION_H_
#define _ROTATION_H_

#include "glm/glm.hpp"

#define X_AXIS (glm::vec3(1.0f, 0.0f, 0.0f))
#define Y_AXIS (glm::vec3(0.0f, 1.0f, 0.0f))
#define Z_AXIS (glm::vec3(0.0f, 0.0f, 1.0f))

struct Rotation {
   Rotation(float angle=0.0, const glm::vec3 axis=X_AXIS) :
      angle(angle),
      axis(axis)
   {}
   float angle; // in degrees
   glm::vec3 axis;
};

#endif
