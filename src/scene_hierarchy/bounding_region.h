#ifndef _BOUNDING_REGION_H_
#define _BOUNDING_REGION_H_

#include <glm/glm.hpp>

enum BoundingRegionType {SPHERICAL, AXIS_ALIGNED, ORIENTED};

class BoundingRegion {
  public:
   BoundingRegion() {}
   virtual ~BoundingRegion() {}

   virtual glm::vec3 GetMin() = 0;
   virtual glm::vec3 GetMax() = 0;

   virtual BoundingRegionType GetType() const = 0;

   static BoundingRegion* GetEmpty() { return NULL; }
};

#endif
