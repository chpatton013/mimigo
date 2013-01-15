#ifndef _PLANET_ROTATER_H_
#define _PLANET_ROTATER_H_

#include <glm/glm.hpp>

#include <iostream>

class MeshNode;

/* Class for rotating a |body| about an arbitrary |center| given a |speed| and
 * an acceleration amount to get to that speed. */
class PlanetRotater {
  public:
   PlanetRotater(const glm::vec3& center, float radius) :
      center_(center),
      radius_(radius),
      angle_(0.0f),
      acceleration_(0.0f)
   {}

   void StartRotatingClockwise(float move_speed, float acceleration);
   void StartRotatingCounterClockwise(float move_speed, float acceleration);
   void StopRotating(float acceleration);
   void Update(MeshNode* mesh);

  private:
   glm::vec3 UpdatedPosition();

   bool is_moving_clockwise() const { return acceleration_ > 0.0f; }
   int CalculateFramesUntilMoveSpeed(float move_speed, float acceleration) {
      return std::abs(move_speed - move_speed_ / acceleration);
   }

   glm::vec3 center_;
   float radius_;
   float angle_;

   float acceleration_;
   float move_speed_;
   int acceleration_frames_;
};

#endif
