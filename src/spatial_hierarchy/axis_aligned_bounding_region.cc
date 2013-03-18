#include "axis_aligned_bounding_region.h"
#include <stdio.h>
#include "bounding_region_component.h"
#include "../core/mesh_load.h"
#include "../util/stl_util.h"

AxisAlignedBoundingRegion::AxisAlignedBoundingRegion(
   const glm::vec3& min_v, const glm::vec3& max_v
) :
   min_(min_v),
   max_(max_v)
{
   static unsigned int instance_num = 0;
   name_ = "aabr_" + toString(instance_num++);

   glm::vec3 tr = center();
   Rotation rot;
   glm::vec3 sc = max() - min();

   create_component(tr, rot, sc, LoadCubeMesh());
}
AxisAlignedBoundingRegion::~AxisAlignedBoundingRegion() {
   delete_component();
}

glm::vec3 AxisAlignedBoundingRegion::center() {
   return min_ + (max_ - min_) * 0.5f;
}
glm::vec3 AxisAlignedBoundingRegion::min() {
   return min_;
}
glm::vec3 AxisAlignedBoundingRegion::max() {
   return max_;
}

void AxisAlignedBoundingRegion::set_center(const glm::vec3& c) {
   glm::vec3 old_center = center();
   glm::vec3 delta = c - old_center;
   min_ += delta;
   max_ += delta;
}
void AxisAlignedBoundingRegion::set_min(const glm::vec3& m) {
   min_ = m;
}
void AxisAlignedBoundingRegion::set_max(const glm::vec3& m) {
   max_ = m;
}

void AxisAlignedBoundingRegion::print() {
   printf(
      "axis-aligned: min:[%.2f,%.2f,%.2f] max:[%.2f,%.2f,%.2f]\n",
      min_.x, min_.y, min_.z, max_.x, max_.y, max_.z
   );
}
