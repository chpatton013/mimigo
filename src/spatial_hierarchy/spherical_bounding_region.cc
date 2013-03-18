#include "spherical_bounding_region.h"
#include <stdio.h>
#include "bounding_region_component.h"
#include "../core/mesh_load.h"
#include "../util/stl_util.h"

SphericalBoundingRegion::SphericalBoundingRegion(const glm::vec3& c, float r) :
   center_(c),
   radius_(r)
{
   static unsigned int instance_num = 0;
   name_ = "sbr_" + toString(instance_num++);

   glm::vec3 tr = center();
   Rotation rot;
   glm::vec3 sc = glm::vec3(radius());

   create_component(tr, rot, sc, LoadSphereMesh());
}
SphericalBoundingRegion::~SphericalBoundingRegion() {
   delete_component();
}

glm::vec3 SphericalBoundingRegion::center() {
   return center_;
}
float SphericalBoundingRegion::radius() {
   return radius_;
}
glm::vec3 SphericalBoundingRegion::min() {
   return center_ - glm::vec3(radius_);
}
glm::vec3 SphericalBoundingRegion::max() {
   return center_ + glm::vec3(radius_);
}

void SphericalBoundingRegion::set_center(const glm::vec3& c) {
   center_ = c;
}
void SphericalBoundingRegion::set_radius(float r) {
   radius_ = r;
}

void SphericalBoundingRegion::print() {
   printf(
      "spherical: c:[%.2f,%.2f,%.2f] r:%.2f\n",
      center_.x, center_.y, center_.z, radius()
   );
}
