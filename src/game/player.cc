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

void Player::MoveBackward() {
   large_planet_mover_.MoveBackward();
}

void Player::TurnLeft() {
   large_planet_mover_.TurnLeft();
}

void Player::TurnRight() {
   large_planet_mover_.TurnRight();
}

void Player::OnUpButtonDown() {
   small_planet_mover_.MoveUp();
}

void Player::OnDownButtonDown() {
   small_planet_mover_.MoveDown();
}

void Player::OnLeftButtonDown() {
   small_planet_mover_.MoveLeft();
}

void Player::OnRightButtonDown() {
   small_planet_mover_.MoveRight();
}

void Player::OnUpButtonUp() {
   small_planet_mover_.StopMoveUp();
}

void Player::OnDownButtonUp() {
   small_planet_mover_.StopMoveDown();
}

void Player::OnLeftButtonUp() {
   small_planet_mover_.StopMoveLeft();
}

void Player::OnRightButtonUp() {
   small_planet_mover_.StopMoveRight();
}

void Player::Jump() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.Jump();
   else
      large_planet_mover_.Jump();
}

void Player::ReleaseJump() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.ReleaseJump();
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
