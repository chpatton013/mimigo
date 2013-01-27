#include "asteroid.h"
#include "planet.h"

Asteroid::Asteroid(Planet *planet, float theta, const std::string& id) :
   theta_(theta),
   planet_(planet),
   radius_(planet->radius() * 5.0f),
   mesh_(SceneNode::Get("asteroid" + id))
{
   UpdateMeshPosition();
}

Asteroid::~Asteroid() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool Asteroid::Update() {
   radius_ -= 0.17f;
   if (radius_ <= planet_->radius() - 0.15f) {
      return false;
   }
   UpdateMeshPosition();
   return true;
}

void Asteroid::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(planet_->center() +
      glm::vec3(glm::cos(theta_), glm::sin(theta_), 0.0f)*radius_));
   mesh_->apply_transformation(glm::scale(0.3f, 0.3f, 0.3f));
}
