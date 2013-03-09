#include <math.h>
#include "checkpoint.h"
#include "planet.h"
#include "../spatial_hierarchy/spherical_bounding_region.h"

inline
float radians(float degrees) {
   return degrees * M_PI / 180.0f;
}

CheckPoint::CheckPoint(Planet *planet, int planet_id, float theta, const std::string& id) :
   planet_(planet),
   planet_id_(planet_id),
   theta_(theta),
   radius_(planet->radius() + 0.1f),
   mesh_(SceneNode::Get(id))
{
   mesh_->set_visible(true);
   UpdateMeshPosition();

   set_bounding_region(new SphericalBoundingRegion(
      position(), mesh_->GetAverageRadius() * 0.25f
   ));
}

CheckPoint::~CheckPoint() {
   RootNode::Instance()->RemoveChild(mesh_);
}

bool CheckPoint::Update() {
   UpdateMeshPosition();
   bounding_region_->set_center(position());
	return true;
}

glm::vec3 CheckPoint::position() {
   return planet_->center() + glm::vec3(
      glm::cos(radians(theta_)),
      glm::sin(radians(theta_)),
      0.0f
   ) * radius_;
}

void CheckPoint::UpdateMeshPosition() {
   mesh_->set_transformation(glm::translate(
      glm::vec3(glm::cos(radians(theta_)), glm::sin(radians(theta_)), 0.0f)*radius_));
   mesh_->apply_transformation(glm::scale(1.5f, 1.5f, 1.5f));
     mesh_->apply_transformation(glm::rotate(glm::mat4(), theta_ - 90.0f, glm::vec3(0.0f,  0.0f, 1.0f)));
}
