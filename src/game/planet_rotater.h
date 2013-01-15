#ifndef _PLANET_ROTATER_H_
#define _PLANET_ROTATER_H_

#include <glm/glm.hpp>

/* Class for rotating a |body| about an arbitrary |center| given a |speed| and
 * an acceleration amount to get to that speed. */
class PlanetRotater {
  public:
   PlanetRotater(const glm::vec3& center) :
      center_(center)
   {}

   void StartRotatingClockwise(float move_speed, float acceleration);
   void StartRotatingCounterClockwise(float move_speed, float acceleration);
   void StopRotating();

  private:
   glm::vec3 center_;
};

#endif
