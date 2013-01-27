#include "swing_asteroid.h"
#include "planet.h"

inline
float radians(float degrees) {
   return degrees * atan(1)*4.0f / 180.0f;
}

SwingAsteroid::SwingAsteroid(Planet *planet, float theta, const std::string& id) :
   planetary_motion_(false),
   planet_(planet),
   theta_(270.0f),
   mesh_(SceneNode::Get("swingasteroid" + id))
{
   position_ = planet->center() + glm::vec3(4.0f, -planet->radius() - .2, 0.0f);
   mesh_->set_visible(true);
   UpdateMeshPosition();
}

SwingAsteroid::~SwingAsteroid() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool SwingAsteroid::Update() {
   if (planetary_motion_) {
      theta_ -= 10.0f;
      position_ = planet_->center() +
         glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet_->radius()+0.2f);
   } else {
      position_ -= glm::vec3(0.2f, 0.0f, 0.0f);
      planetary_motion_ = position_.x < planet_->center().x;
   }
   UpdateMeshPosition();
   return true;
}

void SwingAsteroid::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(position_));
   mesh_->apply_transformation(glm::scale(0.2f, 0.2f, 0.2f));
}
