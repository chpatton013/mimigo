#include "player.h"

Player::Player(Planet* planet, PlayerObserver* observer) :
   small_planet_mover_(NULL, observer),
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
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.MoveUp();
}

void Player::OnDownButtonDown() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.MoveDown();
}

void Player::OnLeftButtonDown() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.MoveLeft();
}

void Player::OnRightButtonDown() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.MoveRight();
}

void Player::OnUpButtonUp() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.StopMoveUp();
   else
      large_planet_mover_.StopMoveForward();
}

void Player::OnDownButtonUp() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.StopMoveDown();
   else
      large_planet_mover_.StopMoveBackward();
}

void Player::OnLeftButtonUp() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.StopMoveLeft();
   else
      large_planet_mover_.StopTurnLeft();
}

void Player::OnRightButtonUp() {
   if (game_play_type_ == GAME_PLAY_SMALL)
      small_planet_mover_.StopMoveRight();
   else
      large_planet_mover_.StopTurnRight();
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
   else if (game_play_type_ == GAME_PLAY_TRANSITION)
      UpdateTransition();
}

void Player::UpdateTransition() {
   if (--transition_frames_ > 0) {
      position_ += velocity_;
      game_play_type_ = GAME_PLAY_LARGE;
   }
   UpdateMeshPosition();
}

void Player::UpdateMeshPosition() {
   glm::mat4 transform;
   transform *= glm::translate(position_);
   SceneNode::Get("player")->set_transformation(transform);
}

void Player::TransitionTo(Planet* planet) {
   if (planet->is_small_planet()) {
      small_planet_mover_.set_planet(planet);
      game_play_type_ = GAME_PLAY_SMALL;
   } else {
      position_ = small_planet_mover_.position();
      large_planet_mover_.set_planet(planet);
      transition_frames_ = 5;
      velocity_ = (large_planet_mover_.position() - position_) / float(transition_frames_);
      game_play_type_ = GAME_PLAY_TRANSITION;
   }
}
