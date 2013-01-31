#ifndef _SPHERICAL_BOUNDING_REGION_H_
#define _SPHERICAL_BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include <stdlib.h>
#include "bounding_region.h"

class SphericalBoundingRegion : public BoundingRegion {
  public:
   SphericalBoundingRegion(const glm::vec3& center, float radius) {
      SetCenter(center);
      SetRadius(radius);
   }
   virtual ~SphericalBoundingRegion() {}

   virtual const glm::vec3& GetCenter() const { return center_; }
   virtual float GetRadius() const { return radius_; }
   virtual glm::vec3 GetMin() { return center_ - glm::vec3(radius_); }
   virtual glm::vec3 GetMax() { return center_ + glm::vec3(radius_); }

   virtual void SetCenter(const glm::vec3& center) { center_ = center; }
   virtual void SetRadius(float radius) { radius_ = radius; }

   virtual BoundingRegionType GetType() const { return SPHERICAL; }

   static SphericalBoundingRegion* empty_;

  private:
   glm::vec3 center_;
   float radius_;
};

#endif
