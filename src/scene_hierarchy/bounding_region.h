#ifndef _BOUNDING_REGION_H_
#define _BOUNDING_REGION_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../core/rotation.h"

enum BoundingRegionType {SPHERICAL, AXIS_ALIGNED, ORIENTED};

class BoundingRegion {
  public:
   BoundingRegion() :
      instance_(1.0f)
   {}
   virtual ~BoundingRegion() {}

   virtual glm::vec3 GetMin() = 0;
   virtual glm::vec3 GetMax() = 0;

   virtual glm::mat4& instance() { return instance_; }
   virtual void set_instance(glm::vec3& t, Rotation& r, glm::vec3& s);

   virtual BoundingRegionType GetType() const = 0;
   virtual void print() = 0;

   static BoundingRegion* GetEmpty() { return NULL; }

  private:
   glm::mat4 instance_;
};

#endif
