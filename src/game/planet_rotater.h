#ifndef _PLANET_ROTATER_H_
#define _PLANET_ROTATER_H_

#include <glm/glm.hpp>

#include <iostream>

/* Class for rotating a |body| about an arbitrary |center| given a |speed| and
 * an acceleration amount to get to that speed. */
class PlanetRotater {
  public:
   PlanetRotater(const glm::vec3& center, float radius) :
      center_(center),
      radius_(radius),
      acceleration_(0.0f)
   {}

   void StartRotatingClockwise(float move_speed, float acceleration);
   void StartRotatingCounterClockwise(float move_speed, float acceleration);
   void StopRotating(float acceleration);
   void Update();

  private:
   bool is_moving_clockwise() const { return acceleration_ > 0.0f; }
   int CalculateFramesUntilMoveSpeed(float move_speed, float acceleration) {
      int frames = std::abs(move_speed - move_speed_ / acceleration);
      std::cout << "num frames = " << frames << std::endl;
      return frames;
   }

   glm::vec3 center_;
   float radius_;

   float acceleration_;
   float move_speed_;
   int acceleration_frames_;
};

#endif
