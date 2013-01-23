#include "large_planet_mover.h"
#include "util/glm_util.h"

static float kJumpSlowdownHeld = 0.01f;
static float kJumpSlowdown = 0.02f;
static float kJumpSpeed = 0.3f;

static float kAngleDelta = 0.5f;
static float kRotateDelta = 3.0f;

static float radians(float degrees) { return degrees/180.0*acos(-1.0); }

LargePlanetMover::LargePlanetMover(Planet* planet) :
   planet_(planet),
   angle_speed_(0.0f),
   rotate_speed_(0.0f),
   jump_speed_(0.0f),
   is_jumping_(false)
{}

void LargePlanetMover::Jump() {
   if (is_jumping_)
      return;

   is_jumping_ = true;
   jump_speed_ = kJumpSpeed;
   std::cout << "start jumping" << std::endl;
}

void LargePlanetMover::Update() {
   UpdateMeshTransform();
   if (rotate_speed_ > 0.0001 || rotate_speed_ < -0.0001) {
      local_rotation_ = glm::rotate(local_rotation_, rotate_speed_, up());
      transform_ = glm::rotate(transform_, -rotate_speed_,
            glm::vec3(transform_[0][1], transform_[1][1], transform_[2][1]));
   }
   if (angle_speed_ > 0.0001 || angle_speed_ < -0.0001) {
      local_rotation_ = glm::rotate(local_rotation_, angle_speed_, right());
      transform_ = glm::rotate(transform_, -angle_speed_,
            glm::vec3(transform_[0][2], transform_[1][2], transform_[2][2]));
      position_ += forward() * (planet_->radius() * std::sin(radians(angle_speed_)) / std::sin(radians(90 - angle_speed_ / 2)));
   }
   if (is_jumping_) {
      position_ += up() * jump_speed_;
      jump_speed_ -= kJumpSlowdown;
      if (jump_speed_ <= 0.0f) {
         jump_speed_ = 0.0f;
         is_jumping_ = false;
      }
   }
}

void LargePlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   position_ = planet_->center() + glm::vec3(0.0f, -planet_->radius(), 0.0f);
   transform_ = glm::rotate(transform_, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
   transform_ = glm::rotate(transform_, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void LargePlanetMover::MoveForward() {
   angle_speed_ = kAngleDelta;
}

void LargePlanetMover::MoveBackward() {
   angle_speed_ = -kAngleDelta;
}

void LargePlanetMover::TurnLeft() {
   rotate_speed_ = kRotateDelta;
}

void LargePlanetMover::TurnRight() {
   rotate_speed_ = -kRotateDelta;
}

void LargePlanetMover::StopMoving() {
   angle_speed_ = 0.0f;
   rotate_speed_ = 0.0f;
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
   glm::mat4 transform = glm::translate(position());
   transform *= transform_;
   SceneNode::Get("player")->set_transformation(transform);
}

void LargePlanetMover::RotateBottomTowardPlanet() {
}
