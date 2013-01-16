#include "player.h"

const float kMoveSpeed = 8.0f;
const float kJumpHeight = 0.18f;
const float kAcceleration = 0.6f;
const float kRotateTime = 0.02f;

// static
void Player::RotationEndCallback(void* p) {
   Player* player = static_cast<Player*>(p);
   player->attach_planet(player->transition_planet_);
}

void Player::StartMovingCounterClockwiseAroundAttachedPlanet() {
   planet_rotater_.StartRotatingCounterClockwise(kMoveSpeed, kAcceleration);
}

void Player::StartMovingClockwiseAroundAttachedPlanet() {
   planet_rotater_.StartRotatingClockwise(kMoveSpeed, kAcceleration);
}

bool Player::IsTopSideOfPlanet() const {
   return true;
}

void Player::StartMovingLeftAroundAttachedPlanet() {
   if (IsTopSideOfPlanet())
      StartMovingCounterClockwiseAroundAttachedPlanet();
   else
      StartMovingClockwiseAroundAttachedPlanet();
}

void Player::StartMovingRightAroundAttachedPlanet() {
   if (IsTopSideOfPlanet())
      StartMovingClockwiseAroundAttachedPlanet();
   else
      StartMovingCounterClockwiseAroundAttachedPlanet();
}

void Player::Jump() {
   planet_rotater_.Jump(kJumpHeight);
}

void Player::StopMoving() {
   planet_rotater_.StopRotating(kAcceleration);
}

bool Player::EntersGravityFieldOf(SmallPlanet* planet) {
   if (planet == attached_planet_)
      return false;

   if (is_jumping() && planet->PositionWithinGravityField(position_)) {
      return true;
   }

   return false;
}

void Player::UpdateMesh() {
   glm::mat4 transform = glm::rotate(planet_rotation_.angle, planet_rotation_.axis);
   transform *= glm::translate(position_);
   transform *= glm::rotate(rotation_.angle, rotation_.axis);
   mesh_->set_transformation(transform);
}

void Player::Update() {
   planet_rotater_.Update(position_, rotation_, &is_jumping_);
   rotater_.Update(rotation_.angle);
   UpdateMesh();
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void Player::RotateBottomToward(SmallPlanet* planet) {
   rotater_.Move(rotation_.angle,
         angle_of(position_ - planet->center()) - 90.0f - rotation_.angle,
         kRotateTime, RotationEndCallback, this);
}

void Player::TransitionTo(SmallPlanet* planet) {
   RotateBottomToward(planet);
   transition_planet_ = planet;
}
