#include "planet_rotater.h"

#include <iostream>
#include "util/glm_util.h"
#include "scene_hierarchy/mesh_node.h"

inline
float clockwise_acceleration(float acceleration) {
   return std::abs(acceleration);
}

inline
float counter_clockwise_acceleration(float acceleration) {
   return -std::abs(acceleration);
}

void PlanetRotater::StartRotatingClockwise(float move_speed,
                                           float acceleration) {
   acceleration_ = clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(
      move_speed, acceleration_);
}

void PlanetRotater::StartRotatingCounterClockwise(float move_speed,
                                                  float acceleration) {
   acceleration_ = counter_clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(
      move_speed, acceleration_);
}

void PlanetRotater::StopRotating(float acceleration) {
   if (is_moving_clockwise())
      acceleration_ = counter_clockwise_acceleration(acceleration);
   else
      acceleration_ = clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(0.0f, acceleration_);
}

void PlanetRotater::Update(SceneNode* node) {
   if (acceleration_frames_ > 0) {
      move_speed_ += acceleration_;
      --acceleration_frames_;
   }
   angle_ -= move_speed_;
   glm::mat4 transform = glm::translate(glm::mat4(1.0f), UpdatedPosition());
   transform = glm::rotate(transform, angle_ - 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
   node->set_transformation(transform);
}

void PlanetRotater::Jump(float jump_velocity) {
   std::cout << "starting a jump" << std::endl;
}

inline float radians(float degrees) {
   return degrees / 180.0f * std::atan(1)*4;
}

glm::vec3 vec3_from_radius_and_angle(float radius, float angle) {
   return glm::vec3(std::cos(radians(angle)), std::sin(radians(angle)), 0.0f) * radius;
}

glm::vec3 PlanetRotater::UpdatedPosition() {
   return center_ + vec3_from_radius_and_angle(radius_, angle_);
}
