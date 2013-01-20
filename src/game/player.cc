#include "player.h"

Player::Player(Planet* planet) :
   small_planet_mover_(planet)
{
   new SceneNode("player");
   RootNode::Instance()->AddChild(SceneNode::Get("player"));
   SceneNode::Get("player")->AddChild(SceneNode::Get("bunny"));
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   TransitionTo(planet);
}

void Player::StartMovingCounterClockwiseAroundAttachedPlanet() {
   //small_planet_mover_.MoveCounterClockwiseAroundPlanet();
   xz_rotation_.angle = 0.0f;
}

void Player::StartMovingClockwiseAroundAttachedPlanet() {
   //small_planet_mover_.MoveClockwiseAroundPlanet();
   xz_rotation_.angle = 180.0f;
}

void Player::OnUpButtonDown(const glm::vec3& camera_pos) {
   small_planet_mover_.MoveUp(camera_pos);
}

void Player::OnDownButtonDown(const glm::vec3& camera_pos) {
   small_planet_mover_.MoveDown(camera_pos);
}

void Player::OnLeftButtonDown(const glm::vec3& camera_pos) {
   small_planet_mover_.MoveLeft(camera_pos);
}

void Player::OnRightButtonDown(const glm::vec3& camera_pos) {
   small_planet_mover_.MoveRight(camera_pos);
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

   return planet->PositionWithinGravityField(small_planet_mover_.position());
}

void Player::UpdateMeshTransform() {
   small_planet_mover_.UpdateMeshTransform();
}

void Player::Update() {
   small_planet_mover_.RotateBottomTowardPlanet();
   small_planet_mover_.Update();
   UpdateMeshTransform();
}

void Player::TransitionTo(Planet* planet) {
   small_planet_mover_.set_planet(planet);
}
