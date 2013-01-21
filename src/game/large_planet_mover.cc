#include "large_planet_mover.h"
#include "util/glm_util.h"

static float kJumpSlowdownHeld = 0.01f;
static float kJumpSlowdown = 0.02f;
static float kJumpSpeed = 0.3f;

void LargePlanetMover::TurnLeft() {
   rotate_type_ = ROTATE_LEFT;
}
void LargePlanetMover::TurnRight() {
   rotate_type_ = ROTATE_RIGHT;
}

void LargePlanetMover::StopMoving() {
   rotate_type_ = ROTATE_NONE;
}

LargePlanetMover::LargePlanetMover(Planet* planet) :
      planet_(planet),
      theta_(90.0f),
      phi_(90.0f),
      rotate_type_(ROTATE_NONE)
{
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
}

inline float radians(float degrees) {
   return degrees * (atan(1)*4.0) / 180.0f;
}

const glm::vec3 LargePlanetMover::position() const {
   return planet_->center() +
      glm::vec3(
         radius_ * std::sin(radians(theta_)) *
                   std::cos(radians(phi_)),
         radius_ * std::sin(radians(theta_)) *
                   std::sin(radians(phi_)),
         radius_ * std::cos(radians(theta_)));
}

void LargePlanetMover::Update() {
   RotateBottomTowardPlanet();

   if (rotate_type_ == ROTATE_LEFT) {
      xz_rotation_.angle += 10.0f;
   } else if (rotate_type_ == ROTATE_RIGHT) {
      xz_rotation_.angle -= 10.0f;
   }

   if (is_jumping_ || is_falling_) {
      if (jump_held_ && jump_speed_ > 0.0f)
         jump_speed_ -= kJumpSlowdownHeld;
      else
         jump_speed_ -= kJumpSlowdown;
      if (jump_speed_ <= 0.0f) {
         is_jumping_ = false;
         is_falling_ = true;
      }
      radius_ += jump_speed_;
      if (radius_ <= planet_->radius()) {
         jump_speed_ = kJumpSpeed;
         radius_ = planet_->radius();
         is_falling_ = false;
      }
   }

   UpdateMeshTransform();
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void LargePlanetMover::FallToPlanet() {
   is_jumping_ = false;
   is_falling_ = true;
}

void LargePlanetMover::RotateBottomTowardPlanet() {
   xy_rotation_.angle = angle_of(position() - planet_->center()) - 90.0f;
}

void LargePlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform;
   transform *= glm::translate(position());
   transform *= glm::rotate(xy_rotation_.angle, xy_rotation_.axis);
   transform *= glm::rotate(xz_rotation_.angle, xz_rotation_.axis);
   SceneNode::Get("player")->set_transformation(transform);
}

void LargePlanetMover::MoveForward() {
   phi_ += 0.10f;
}

void LargePlanetMover::MoveBackward() {
   phi_ -= 0.10f;
}

void LargePlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   FallToPlanet();
}
