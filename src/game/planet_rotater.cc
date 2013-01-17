#include "planet_rotater.h"

#include <iostream>
#include "util/glm_util.h"
#include "scene_hierarchy/mesh_node.h"

const float kJumpSpeed = 0.04f;

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
   final_move_speed_ = move_speed;
}

void PlanetRotater::StartRotatingCounterClockwise(float move_speed,
                                                  float acceleration) {
   acceleration_ = counter_clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(
      move_speed, acceleration_);
   final_move_speed_ = -move_speed;
}

void PlanetRotater::StartMoving(const glm::vec3& direction, float move_speed, float acceleration) {
}

void PlanetRotater::StopRotating(float acceleration) {
   if (is_moving_clockwise())
      acceleration_ = counter_clockwise_acceleration(acceleration);
   else
      acceleration_ = clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(0.0f, acceleration_);
   final_move_speed_ = 0.0f;
}

void PlanetRotater::Update(glm::vec3& position, Rotation& rotation,
                           bool* is_jumping) {
   if (acceleration_frames_ > 0) {
      move_speed_ += acceleration_;
      --acceleration_frames_;
   } else {
      move_speed_ = final_move_speed_;
   }

   if (radius_ < destination_radius_) {
      radius_ += kJumpSpeed;
      *is_jumping = true;
      if (radius_ >= destination_radius_) {
         destination_radius_ = planet_radius_;
         *is_jumping = false;
      }
   }
   else if (radius_ > destination_radius_) {
      radius_ -= kJumpSpeed;
      if (radius_ < destination_radius_) {
         radius_ = destination_radius_ = planet_radius_;
      }
   }

   angle_ -= move_speed_;
   rotation.angle -= move_speed_;
   position = UpdatedPosition();
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void PlanetRotater::SetAngleToNearestPosition(const glm::vec3& position) {
   angle_ = angle_of(position - center_);
}

void PlanetRotater::Jump(float jump_height) {
   destination_radius_ = planet_radius_ + jump_height;
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
