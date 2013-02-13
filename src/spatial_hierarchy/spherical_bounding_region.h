#ifndef _SPHERICAL_BOUNDING_REGION_H_
#define _SPHERICAL_BOUNDING_REGION_H_

#include <stdio.h>
#include <glm/glm.hpp>
#include "bounding_region.h"
#include "../gl/gl_mesh.h"

class SphericalBoundingRegion : public BoundingRegion {
  public:
   SphericalBoundingRegion(const glm::vec3& c, float r) :
      center_(c),
      radius_(r)
   {}
   virtual ~SphericalBoundingRegion() {}

   virtual glm::vec3 center() { return center_; }
   virtual float radius() { return radius_; }
   virtual glm::vec3 min() { return center_ - glm::vec3(radius_); }
   virtual glm::vec3 max() { return center_ + glm::vec3(radius_); }

   virtual void set_center(const glm::vec3& c) { center_ = c; }
   virtual void set_radius(float r) { radius_ = r; }

   virtual void print() {
      printf(
         "spherical: c:[%.2f,%.2f,%.2f] r:%.2f\n",
         center_.x, center_.y, center_.z, radius()
      );
   }

  private:
   glm::vec3 center_;
   float radius_;
};

#endif
