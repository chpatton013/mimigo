#ifndef _PLANET_ROTATER_H_
#define _PLANET_ROTATER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"

#include <iostream>

class Animator;

/* Class for rotating a |body| about an arbitrary |center| given a |speed| and
 * an acceleration amount to get to that speed. */
class PlanetRotater {
  public:
   PlanetRotater(const glm::vec3& center, float radius) :
      center_(center),
      radius_(radius),
      destination_radius_(radius),
      planet_radius_(radius),
      angle_(0.0f),
      acceleration_(0.0f)
   {}

   void StartRotatingClockwise(float move_speed, float acceleration);
   void StartRotatingCounterClockwise(float move_speed, float acceleration);
   void StopRotating(float acceleration);
   void Update(glm::vec3& position, Rotation& rotation);
   void Jump(float jump_height);

  private:
   glm::vec3 UpdatedPosition();

   bool is_moving_clockwise() const { return acceleration_ > 0.0f; }
   int CalculateFramesUntilMoveSpeed(float move_speed, float acceleration)
    { return std::abs(move_speed - move_speed_ / acceleration); }

   glm::vec3 center_;
   float radius_;
   float destination_radius_;
   float planet_radius_;
   float angle_;

   float acceleration_;
   float move_speed_;
   int acceleration_frames_;
};

#endif
