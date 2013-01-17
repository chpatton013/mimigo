#include "planet_rotater.h"

#include <iostream>
#include <SDL/SDL.h>
#include "core/linear_value_animator.h"
#include "util/glm_util.h"
#include "scene_hierarchy/mesh_node.h"

static LinearValueAnimator<float>* rotater = NULL;
static LinearValueAnimator<float>* jumper = NULL;

inline
float clockwise_acceleration(float acceleration) {
   return std::abs(acceleration);
}

inline
float counter_clockwise_acceleration(float acceleration) {
   return -std::abs(acceleration);
}

void RotationEnd(void*) {
   if (rotater) {
      delete rotater;
      rotater = NULL;
   }
   if (jumper) {
      delete jumper;
      jumper = NULL;
   }
}

void PlanetRotater::StartRotatingClockwise(float move_speed, float) {
   Callback callback(RotationEnd, this);
   rotater = new LinearValueAnimator<float>(&move_speed_, move_speed, 0.5f, callback, SDL_GetTicks());
}

void PlanetRotater::StartRotatingCounterClockwise(float move_speed, float) {
   Callback callback(RotationEnd, this);
   rotater = new LinearValueAnimator<float>(&move_speed_, -move_speed, 0.5f, callback, SDL_GetTicks());
}

void PlanetRotater::StartMoving(const glm::vec3& direction, float move_speed, float acceleration) {
}

void PlanetRotater::StopRotating(float acceleration) {
   Callback callback(RotationEnd, this);
   rotater = new LinearValueAnimator<float>(&move_speed_, -move_speed_, 0.5f, callback, SDL_GetTicks());
}

void PlanetRotater::Update(glm::vec3& position, Rotation& rotation,
                           bool* is_jumping) {
   angle_ -= move_speed_;
   rotation.angle -= move_speed_;
   position = UpdatedPosition();

   if (rotater)
      rotater->Update(SDL_GetTicks());
   if (jumper) {
      *is_jumping = true;
      jumper->Update(SDL_GetTicks());
   } else {
      *is_jumping = false;
   }
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void PlanetRotater::SetAngleToNearestPosition(const glm::vec3& position) {
   angle_ = angle_of(position - center_);
}

void JumpEnd(void* void_planet_rotater) {
   std::cout << "jump end" << std::endl;
   PlanetRotater* planet_rotater = (PlanetRotater*)(void_planet_rotater);
   planet_rotater->Fall();
}

void PlanetRotater::Fall() {
   Callback callback(RotationEnd, this);
   jumper = new LinearValueAnimator<float>(&radius_, planet_radius_ - radius_, 0.08f, callback, SDL_GetTicks());
}

void PlanetRotater::Jump(float jump_height) {
   Callback callback(JumpEnd, this);
   jumper = new LinearValueAnimator<float>(&radius_, jump_height, 0.05f, callback, SDL_GetTicks());
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
