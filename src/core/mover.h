#ifndef MOVER_H_
#define MOVER_H_

#include <cmath>
#include "../util/glm_util.h"
#include "../util/stl_util.h"

namespace {
void correct_angle(float& angle) {
   while (angle < 0.0f)
      angle += 360.0f;
   while (angle > 360.0f)
      angle -= 360.0f;
}
}

class Rotater {
  public:
   Rotater() : rotated_(0.0f), rotate_speed_(0.0f), final_rotation_(NULL) {}

   void Update(float& rotation);
   void Move(float& current_rotate, float rotate_amount, float seconds);
   void Spin(float& current_rotate, float rotate_speed, float seconds);

  private:
   float rotated_;
   float rotate_speed_;
   float* final_rotation_;
};

class Mover {
  public:
   Mover() : move_to_(NULL) {}
   void Update(glm::vec3& position);
   void Move(const glm::vec3& pos, const glm::vec3& where, float seconds);

  private:
   glm::vec3* move_to_;
   float move_speed_;
};

#endif
