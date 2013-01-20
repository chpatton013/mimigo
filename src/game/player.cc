#include "player.h"

Player::Player(Planet* planet) :
   small_planet_mover_(NULL),
   large_planet_mover_(NULL)
{
   new SceneNode("player");
   RootNode::Instance()->AddChild(SceneNode::Get("player"));
   SceneNode::Get("player")->AddChild(SceneNode::Get("bunny"));
}

void Player::MoveForward() {
   large_planet_mover_.MoveForward();
}

void Player::TurnLeft() {
   large_planet_mover_.TurnLeft();
}

void Player::TurnRight() {
   large_planet_mover_.TurnRight();
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
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.Jump();
   else
      large_planet_mover_.Jump();
}

void Player::StopMoving() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.StopMoving();
   else
      large_planet_mover_.StopMoving();
}

bool Player::EntersGravityFieldOf(Planet* planet) {
   if (is_attached_to(planet))
      return false;

   return planet->PositionWithinGravityField(position());
}

void Player::Update() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.Update();
   else if (game_play_type_ == GAME_PLAY_LARGE)
      large_planet_mover_.Update();
}

void Player::TransitionTo(Planet* planet) {
   if (planet->is_small_planet()) {
      small_planet_mover_.set_planet(planet);
      game_play_type_ = GAME_PLAY_SMALL;
   } else {
      large_planet_mover_.set_planet(planet);
      game_play_type_ = GAME_PLAY_LARGE;
   }
}
