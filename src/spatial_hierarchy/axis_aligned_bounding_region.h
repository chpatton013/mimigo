#ifndef _AXIS_ALIGNED_BOUNDING_REGION_H_
#define _AXIS_ALIGNED_BOUNDING_REGION_H_

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include "bounding_region.h"
#include "../gl/gl_mesh.h"

class AxisAlignedBoundingRegion : public BoundingRegion {
  public:
   AxisAlignedBoundingRegion(const glm::vec3& min_v, const glm::vec3& max_v) :
      min_(min_v),
      max_(max_v)
   {}
   virtual ~AxisAlignedBoundingRegion() {}

   virtual glm::vec3 center() {
      return min_ + (max_ - min_) * 0.5f;
   }
   virtual glm::vec3 min() { return min_; }
   virtual glm::vec3 max() { return max_; }

   virtual void set_center(const glm::vec3& c) {
      glm::vec3 old_center = center();
      glm::vec3 delta = c - old_center;
      min_ += delta;
      max_ += delta;
   }
   virtual void set_min(const glm::vec3& m) { min_ = m; }
   virtual void set_max(const glm::vec3& m) { max_ = m; }

   virtual void print() {
      printf(
         "axis-aligned: min:[%.2f,%.2f,%.2f] max:[%.2f,%.2f,%.2f]\n",
         min_.x, min_.y, min_.z, max_.x, max_.y, max_.z
      );
   }

  private:
   glm::vec3 min_, max_;
};

#endif
