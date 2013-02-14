#include "swing_asteroid.h"
#include "planet.h"
#include "../spatial_hierarchy/spherical_bounding_region.h"

inline
float radians(float degrees) {
   return degrees * atan(1)*4.0f / 180.0f;
}

SwingAsteroid::SwingAsteroid(Planet *planet, float theta, const std::string& id, bool cw) :
   planetary_motion_(false),
   planet_(planet),
   theta_(theta),
   cw_(cw),
   mesh_(SceneNode::Get(id))
{
   if (theta_ == 270.0f)
      position_ = planet->center() + glm::vec3(4.0f, -planet->radius() - .2, 0.0f);
   else
      position_ = planet->center() + glm::vec3(4.0f, planet->radius() + .2, 0.0f);
   mesh_->set_visible(true);
   UpdateMeshPosition();

   set_bounding_region(new SphericalBoundingRegion(
      position(), mesh_->GetAverageRadius() * 0.25f
   ));
}

SwingAsteroid::~SwingAsteroid() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool SwingAsteroid::Update() {
   if (planetary_motion_) {
      if (cw_)
         theta_ += 10.0f;
      else
         theta_ -= 10.0f;
      position_ = planet_->center() +
         glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet_->radius()+0.2f);
   } else {
      position_ -= glm::vec3(0.2f, 0.0f, 0.0f);
      planetary_motion_ = position_.x < planet_->center().x;
   }
   UpdateMeshPosition();
   bounding_region_->set_center(position());

   return true;
}

void SwingAsteroid::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(position_));
   mesh_->apply_transformation(glm::scale(0.2f, 0.2f, 0.2f));
}
