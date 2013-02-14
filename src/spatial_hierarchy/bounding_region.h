#ifndef _BOUNDING_REGION_H_
#define _BOUNDING_REGION_H_

#include <glm/glm.hpp>

class BoundingRegion {
  public:
   BoundingRegion() {}
   virtual ~BoundingRegion() {}

   virtual glm::vec3 center() = 0;
   virtual glm::vec3 min() = 0;
   virtual glm::vec3 max() = 0;

   virtual void set_center(const glm::vec3& c) = 0;

   virtual void print() = 0;
};

#endif
