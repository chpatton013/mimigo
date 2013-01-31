#ifndef _AXIS_ALIGNED_BOUNDING_REGION_H_
#define _AXIS_ALIGNED_BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include <stdio.h>
#include <vector>
#include "bounding_region.h"

class AxisAlignedBoundingRegion : public BoundingRegion {
  public:
   AxisAlignedBoundingRegion(const glm::vec3& min, const glm::vec3& max) {
      SetMin(min);
      SetMax(max);
   }
   virtual ~AxisAlignedBoundingRegion() {}

   virtual glm::vec3 GetMin() { return min_; }
   virtual glm::vec3 GetMax() { return max_; }

   virtual void SetMin(const glm::vec3& min) { min_ = min; }
   virtual void SetMax(const glm::vec3& max) { max_ = max; }

   virtual BoundingRegionType GetType() const { return AXIS_ALIGNED; }
   virtual void print() {
      printf(
         "axis-aligned: min:[%.2f,%.2f,%.2f] max:[%.2f,%.2f,%.2f]\n",
         min_.x, min_.y, min_.z, max_.x, max_.y, max_.z
      );
   }

   static BoundingRegion* GetEmpty() {
      return empty_ == NULL ?
         empty_ = new AxisAlignedBoundingRegion(glm::vec3(0.0f), glm::vec3(0.0f)) :
         empty_;
   }

   static AxisAlignedBoundingRegion* empty_;

  private:
   glm::vec3 min_, max_;
};

#endif
