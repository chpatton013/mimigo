#include "player.h"

Player::Player(Planet* planet) :
   small_planet_mover_(planet)
{
   new SceneNode("player");
   RootNode::Instance()->AddChild(SceneNode::Get("player"));
   SceneNode::Get("player")->AddChild(SceneNode::Get("bunny"));
   TransitionTo(planet);
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

void Player::Update() {
   small_planet_mover_.RotateBottomTowardPlanet();
   small_planet_mover_.Update();
   small_planet_mover_.UpdateMeshTransform();
}

void Player::TransitionTo(Planet* planet) {
   small_planet_mover_.set_planet(planet);
}
