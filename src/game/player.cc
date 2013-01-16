#include "player.h"

const float kMoveSpeed = 8.0f;
const float kJumpHeight = 0.18f;
const float kAcceleration = 0.6f;

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

void Player::UpdateMesh() {
   glm::mat4 transform = glm::rotate(planet_rotation_.angle, planet_rotation_.axis);
   transform *= glm::translate(position_);
   transform *= glm::rotate(rotation_.angle, rotation_.axis);
   mesh_->set_transformation(transform);
}

void Player::Update() {
   planet_rotater_.Update(position_, rotation_);
   UpdateMesh();
}

void Player::RotateBottomToward(SmallPlanet* planet) {
}

void Player::TransitionTo(SmallPlanet* planet) {
   RotateBottomToward(planet);
   attach_planet(planet);
}
