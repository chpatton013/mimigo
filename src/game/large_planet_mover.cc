#include "large_planet_mover.h"
#include "util/glm_util.h"

static float kJumpSlowdownHeld = 0.01f;
static float kJumpSlowdown = 0.02f;
static float kJumpSpeed = 0.3f;

static float kAngleDelta = 0.5f;
static float kRotateDelta = 15.0f;

static float radians(float degrees) { return degrees/180.0*acos(-1.0); }

LargePlanetMover::LargePlanetMover(Planet* planet) :
   planet_(planet),
   angle_speed_(0.0f)
{}

void LargePlanetMover::Update() {
   UpdateMeshTransform();
   if (angle_speed_ > 0.0001 || angle_speed_ < 0.0001) {
      local_rotation_ = glm::rotate(local_rotation_, angle_speed_, right());
      position_ += forward() * (planet_->radius() * std::sin(radians(angle_speed_)) / std::sin(radians(90 - angle_speed_ / 2)));
   }
}

void LargePlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   position_ = planet_->center() + glm::vec3(0.0f, -planet_->radius(), 0.0f);
}

void LargePlanetMover::MoveForward() {
   angle_speed_ = kAngleDelta;
}

void LargePlanetMover::MoveBackward() {
   angle_speed_ = -kAngleDelta;
}

void LargePlanetMover::TurnLeft() {
   local_rotation_ = glm::rotate(local_rotation_, kRotateDelta, up());
}

void LargePlanetMover::TurnRight() {
   local_rotation_ = glm::rotate(local_rotation_, -kRotateDelta, up());
}

void LargePlanetMover::StopMoving() {
   angle_speed_ = 0.0f;
}

void LargePlanetMover::FallToPlanet() {
}

const glm::vec3 LargePlanetMover::position() const {
   return position_;
}

const glm::vec3 LargePlanetMover::forward() const {
   return glm::vec3(local_rotation_[0][2], local_rotation_[1][2], local_rotation_[2][2]);
}

const glm::vec3 LargePlanetMover::right() const {
   return glm::vec3(local_rotation_[0][0], local_rotation_[1][0], local_rotation_[2][0]);
}

const glm::vec3 LargePlanetMover::up() const {
   return glm::vec3(local_rotation_[0][1], local_rotation_[1][1], local_rotation_[2][1]);
}

void LargePlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform;
   transform *= glm::translate(position());
   glm::mat4 r = glm::rotate(local_rotation_, 180.0f, forward());
   r = glm::rotate(r, 90.0f, up());
   transform *= r;
   SceneNode::Get("player")->set_transformation(transform);
}

void LargePlanetMover::RotateBottomTowardPlanet() {
}
