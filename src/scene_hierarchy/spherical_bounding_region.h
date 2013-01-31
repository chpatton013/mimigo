#ifndef _SPHERICAL_BOUNDING_REGION_H_
#define _SPHERICAL_BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "bounding_region.h"

class SphericalBoundingRegion : public BoundingRegion {
  public:
   SphericalBoundingRegion(const glm::vec3& center, float radius) {
      SetCenter(center);
      SetRadius(radius);
   }
   virtual ~SphericalBoundingRegion() {}

   virtual glm::vec3 GetCenter() {
      return glm::vec3(instance() * glm::vec4(center_, 1.0f));
   }
   virtual float GetRadius() {
      glm::vec3 origin = glm::vec3(instance() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
      glm::vec3 scaled_radius = glm::vec3(instance() * glm::vec4(radius_, 0.0f, 0.0f, 1.0f));
      glm::vec3 diff = scaled_radius - origin;
      return sqrt(glm::dot(diff, diff));
   }
   virtual glm::vec3 GetMin() { return GetCenter() - glm::vec3(GetRadius()); }
   virtual glm::vec3 GetMax() { return GetCenter() + glm::vec3(GetRadius()); }

   virtual void SetCenter(const glm::vec3& center) { center_ = center; }
   virtual void SetRadius(float radius) { radius_ = radius; }

   virtual BoundingRegionType GetType() const { return SPHERICAL; }
   virtual void print() {
      printf(
         "spherical: c:[%.2f,%.2f,%.2f] r:%.2f\n",
         GetCenter().x, GetCenter().y, GetCenter().z, GetRadius()
      );
   }

   static SphericalBoundingRegion* empty_;

  private:
   glm::vec3 center_;
   float radius_;
};

#endif
