#include "large_planet_mover.h"

void LargePlanetMover::TurnLeft() { xz_rotation_.angle += 20; }
void LargePlanetMover::TurnRight() { xz_rotation_.angle -= 20; }

LargePlanetMover::LargePlanetMover(Planet* planet) {
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
}

void LargePlanetMover::Update() {
   UpdateMeshTransform();
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
