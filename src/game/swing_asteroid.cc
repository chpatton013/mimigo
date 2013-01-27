#include "swing_asteroid.h"
#include "planet.h"

inline
float radians(float degrees) {
   return degrees * atan(1)*4.0f / 180.0f;
}

SwingAsteroid::SwingAsteroid(Planet *planet, float theta, const std::string& id) :
   theta_(theta),
   planet_(planet),
   radius_(planet->radius() * 5.0f),
   mesh_(SceneNode::Get("swingasteroid" + id))
{
   mesh_->set_visible(true);
   UpdateMeshPosition();
}

SwingAsteroid::~SwingAsteroid() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool SwingAsteroid::Update() {
   radius_ -= 0.17f;
   if (radius_ <= planet_->radius() - 0.15f)
      return false;
   UpdateMeshPosition();
   return true;
}

void SwingAsteroid::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(planet_->center() +
      glm::vec3(glm::cos(radians(theta_)), glm::sin(radians(theta_)), 0.0f)*radius_));
   mesh_->apply_transformation(glm::scale(0.3f, 0.3f, 0.3f));
}
