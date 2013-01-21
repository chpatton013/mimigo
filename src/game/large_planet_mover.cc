#include "large_planet_mover.h"

void LargePlanetMover::TurnLeft() { xz_rotation_.angle += 20; }
void LargePlanetMover::TurnRight() { xz_rotation_.angle -= 20; }

LargePlanetMover::LargePlanetMover(Planet* planet) :
      planet_(planet),
      planet_rotater_(NULL)
{
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
}

void LargePlanetMover::Update() {
   RotateBottomTowardPlanet();
   planet_rotater_->Update(position_, xy_rotation_, &is_jumping_);
   UpdateMeshTransform();
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void LargePlanetMover::RotateBottomTowardPlanet() {
   xy_rotation_.angle = angle_of(position_ - planet_->center()) - 90.0f;
}

void LargePlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform;
   transform *= glm::translate(position_);
   transform *= glm::rotate(xy_rotation_.angle, xy_rotation_.axis);
   transform *= glm::rotate(xz_rotation_.angle, xz_rotation_.axis);
   SceneNode::Get("player")->set_transformation(transform);
}

void LargePlanetMover::MoveForward() {
}

void LargePlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   if (planet_rotater_)
      delete planet_rotater_;
   planet_rotater_ = new PlanetRotater(planet->center(), planet->radius(), position_);
}
