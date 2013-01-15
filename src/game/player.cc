#include "player.h"

const float kMoveSpeed = 10.0f;
const float kAcceleration = 1.0f;

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

void Player::StopMoving() {
   rotater_.StopRotating(kAcceleration);
}

void Player::Update() {
   rotater_.Update();
}
