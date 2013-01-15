#include "player.h"

const float kMoveSpeed = 8.0f;
const float kJumpSpeed = 0.1f;
const float kAcceleration = 0.6f;

void Player::StartMovingCounterClockwiseAroundAttachedPlanet() {
   rotater_.StartRotatingCounterClockwise(kMoveSpeed, kAcceleration);
}

void Player::StartMovingClockwiseAroundAttachedPlanet() {
   rotater_.StartRotatingClockwise(kMoveSpeed, kAcceleration);
}

bool Player::IsTopSideOfPlanet() const {
   return true;
}

void Player::StartMovingLeftAroundAttachedPlanet() {
   if (IsTopSideOfPlanet()) {
      StartMovingCounterClockwiseAroundAttachedPlanet();
   }
   else {
      StartMovingClockwiseAroundAttachedPlanet();
   }
}

void Player::StartMovingRightAroundAttachedPlanet() {
   if (IsTopSideOfPlanet()) {
      StartMovingClockwiseAroundAttachedPlanet();
   }
   else {
      StartMovingCounterClockwiseAroundAttachedPlanet();
   }
}

void Player::Jump() {
   rotater_.Jump(kJumpSpeed);
}

void Player::StopMoving() {
   rotater_.StopRotating(kAcceleration);
}

void Player::Update() {
   rotater_.Update(mesh_);
}
