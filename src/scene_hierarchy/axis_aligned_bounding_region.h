#ifndef _AXIS_ALIGNED_BOUNDING_REGION_H_
#define _AXIS_ALIGNED_BOUNDING_REGION_H_

#include <glm/glm.hpp>
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
