#include "planet_rotater.h"

#include <iostream>
#include "util/glm_util.h"

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

glm::vec3 PlanetRotater::Update() {
   if (acceleration_frames_ > 0) {
      move_speed_ += acceleration_;
      --acceleration_frames_;
   }
   angle_ += move_speed_;
   glm::vec3 temp = UpdatedPosition();
   glm_util::Print(temp);
   return temp;
}

inline float radians(float degrees) {
   return degrees / 180.0f * std::atan(1)*4;
}

glm::vec3 vec3_from_radius_and_angle(float radius, float angle) {
   return glm::vec3(std::cos(radians(angle)), std::sin(radians(angle)), 0.0f) * radius;
}

glm::vec3 PlanetRotater::UpdatedPosition() {
   std::cout << angle_ << std::endl;
   return center_ + vec3_from_radius_and_angle(radius_, angle_);
}
