#include "player.h"

Player::Player(Planet* planet) :
   small_planet_mover_(planet, position_, xy_rotation_)
{
   new SceneNode("player");
   RootNode::Instance()->AddChild(SceneNode::Get("player"));
   SceneNode::Get("player")->AddChild(SceneNode::Get("bunny"));
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   TransitionTo(planet);
}

void Player::StartMovingCounterClockwiseAroundAttachedPlanet() {
   small_planet_mover_.MoveCounterClockwiseAroundPlanet();
   xz_rotation_.angle = 0.0f;
}

void Player::StartMovingClockwiseAroundAttachedPlanet() {
   small_planet_mover_.MoveClockwiseAroundPlanet();
   xz_rotation_.angle = 180.0f;
}

void Player::StartMovingUpAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (small_planet_mover_.IsRightSideOfPlanet())
      StartMovingCounterClockwiseAroundAttachedPlanet();
   else
      StartMovingClockwiseAroundAttachedPlanet();
}

void Player::StartMovingDownAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (small_planet_mover_.IsRightSideOfPlanet())
      StartMovingClockwiseAroundAttachedPlanet();
   else
      StartMovingCounterClockwiseAroundAttachedPlanet();
}

void Player::StartMovingLeftAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (small_planet_mover_.IsTopSideOfPlanet())
      StartMovingCounterClockwiseAroundAttachedPlanet();
   else
      StartMovingClockwiseAroundAttachedPlanet();
}

void Player::StartMovingRightAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (small_planet_mover_.IsTopSideOfPlanet())
      StartMovingClockwiseAroundAttachedPlanet();
   else
      StartMovingCounterClockwiseAroundAttachedPlanet();
}

void Player::Jump() {
   small_planet_mover_.Jump();
}

void Player::StopMoving() {
   small_planet_mover_.StopMoving();
}

bool Player::EntersGravityFieldOf(Planet* planet) {
   if (is_attached_to(planet))
      return false;

   return planet->PositionWithinGravityField(position_);
}

void Player::UpdateMeshTransform() {
   glm::mat4 transform;
   transform *= glm::translate(position_);
   transform *= glm::rotate(xy_rotation_.angle, xy_rotation_.axis);
   transform *= glm::rotate(xz_rotation_.angle, xz_rotation_.axis);
   SceneNode::Get("player")->set_transformation(transform);
}

void Player::Update() {
   small_planet_mover_.RotateBottomTowardPlanet();
   small_planet_mover_.Update();
   UpdateMeshTransform();
}

void Player::TransitionTo(Planet* planet) {
   small_planet_mover_.set_planet(planet);
}
