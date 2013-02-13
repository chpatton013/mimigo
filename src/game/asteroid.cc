#include <math.h>
#include "asteroid.h"
#include "planet.h"
#include "../spatial_hierarchy/spherical_bounding_region.h"

inline
float radians(float degrees) {
   return degrees * M_PI / 180.0f;
}

Asteroid::Asteroid(Planet *planet, float theta, const std::string& id) :
   planet_(planet),
   theta_(theta),
   radius_(planet->radius() * 5.0f),
   mesh_(SceneNode::Get(id))
{
   mesh_->set_visible(true);
   UpdateMeshPosition();

   set_bounding_region(new SphericalBoundingRegion(
      position(), mesh_->GetAverageRadius() * 0.25f
   ));
}

Asteroid::~Asteroid() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool Asteroid::Update() {
   radius_ -= 0.2f;
   if (radius_ <= planet_->radius() - 0.15f)
      return false;
   UpdateMeshPosition();
   bounding_region_->set_center(position());
   return true;
}

glm::vec3 Asteroid::position() {
   return planet_->center() + glm::vec3(
      glm::cos(radians(theta_)),
      glm::sin(radians(theta_)),
      0.0f
   ) * radius_;
}

void Asteroid::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(planet_->center() +
      glm::vec3(glm::cos(radians(theta_)), glm::sin(radians(theta_)), 0.0f)*radius_));
   mesh_->apply_transformation(glm::scale(0.3f, 0.3f, 0.3f));
}
