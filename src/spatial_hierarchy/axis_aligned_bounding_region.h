#ifndef _AXIS_ALIGNED_BOUNDING_REGION_H_
#define _AXIS_ALIGNED_BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include "bounding_region.h"

class AxisAlignedBoundingRegion : public BoundingRegion {
  public:
   AxisAlignedBoundingRegion(const glm::vec3& min_v, const glm::vec3& max_v);
   virtual ~AxisAlignedBoundingRegion();

   virtual glm::vec3 center();
   virtual glm::vec3 min();
   virtual glm::vec3 max();

   virtual void set_center(const glm::vec3& c);
   virtual void set_min(const glm::vec3& m);
   virtual void set_max(const glm::vec3& m);

   virtual void print();

  protected:
   glm::vec3 min_, max_;
};

#endif
