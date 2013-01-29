#include "large_planet_mover.h"
#include "player.h"
#include "util/glm_util.h"

static float kJumpSlowdownHeld = 0.01f;
static float kJumpSlowdown = 0.017f;
static float kJumpSpeed = 0.2f;

static float kAngleDelta = 0.5f;
static float kAngleAcceleration = 0.1f;
static float kRotateDelta = 3.0f;

static float radians(float degrees) { return degrees/180.0*acos(-1.0); }

LargePlanetMover::LargePlanetMover(Planet* planet) :
   planet_(planet),
   angle_speed_(0.0f),
   rotate_speed_(0.0f),
   move_forward_(false),
   move_backward_(false),
   turn_left_(false),
   turn_right_(false),
   jump_speed_(0.0f),
   is_jumping_(false)
{}

void LargePlanetMover::Jump() {
   if (is_jumping_)
      return;

   is_jumping_ = true;
   jump_speed_ = kJumpSpeed;
}

inline
float current_radius(const glm::vec3& position, const glm::vec3& center) {
   return glm_util::magnitude(position-center);
}

void LargePlanetMover::Update() {
   if (move_forward_)
      angle_speed_ = std::min(kAngleDelta, angle_speed_ + kAngleAcceleration);
   else if (move_backward_)
      angle_speed_ = std::max(-kAngleDelta, angle_speed_ - kAngleAcceleration);
   else {
      if (angle_speed_ < 0.0f)
         angle_speed_ = std::min(0.0f, angle_speed_ + kAngleAcceleration);
      else
         angle_speed_ = std::max(0.0f, angle_speed_ - kAngleAcceleration);
   }

   if (turn_left_) {
      rotate_speed_ = kRotateDelta;
   } else if (turn_right_) {
      rotate_speed_ = -kRotateDelta;
   } else {
      rotate_speed_ = 0.0f;
   }

   local_rotation_ = glm::rotate(local_rotation_, -rotate_speed_, up());
   local_rotation_ = glm::rotate(local_rotation_, -angle_speed_, right());
   position_ += forward() * ((planet_->radius()+0.15f) * std::sin(radians(angle_speed_)) / std::sin(radians(90 - angle_speed_ / 2)));

   if (is_jumping_) {
      position_ += up() * jump_speed_;
      jump_speed_ -= kJumpSlowdown;
      if (current_radius(position_, planet_->center()) <= planet_->radius()+0.15f) {
         jump_speed_ = 0.0f;
         is_jumping_ = false;
         position_ += up() * (current_radius(position_, planet_->center()) - (planet_->radius()+0.15f));
      }
   }
   if (observer_)
      observer_->OnPlayerMove(position_, up(), forward());
   UpdateMeshTransform();
}

void LargePlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   position_ = planet_->center() + glm::vec3(0.0f, -planet_->radius()-0.15f, 0.0f);
   local_rotation_ = glm::rotate(local_rotation_, 180.0f, forward());
}

void LargePlanetMover::MoveForward() { move_forward_ = true; }
void LargePlanetMover::MoveBackward() { move_backward_ = true; }
void LargePlanetMover::TurnLeft() { turn_left_ = true; }
void LargePlanetMover::TurnRight() { turn_right_ = true; }
void LargePlanetMover::StopMoveForward() { move_forward_ = false; }
void LargePlanetMover::StopMoveBackward() { move_backward_ = false; }
void LargePlanetMover::StopTurnLeft() { turn_left_ = false; }
void LargePlanetMover::StopTurnRight() { turn_right_ = false; }

const glm::vec3 LargePlanetMover::position() const {
   return position_;
}

// COLUMN-MAJOR Order, awesome
const glm::vec3 LargePlanetMover::forward() const {
   return glm::vec3(local_rotation_[2][0], local_rotation_[2][1], local_rotation_[2][2]);
}

const glm::vec3 LargePlanetMover::right() const {
   return glm::vec3(local_rotation_[0][0], local_rotation_[0][1], local_rotation_[0][2]);
}

const glm::vec3 LargePlanetMover::up() const {
   return glm::vec3(local_rotation_[1][0], local_rotation_[1][1], local_rotation_[1][2]);
}

void LargePlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform = glm::translate(position());
   transform *= local_rotation_;
   SceneNode::Get("player")->set_transformation(transform);
}

void LargePlanetMover::RotateBottomTowardPlanet() {
}
