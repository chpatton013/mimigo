#include "scene_hierarchy/spherical_bounding_region.h"

SphericalBoundingRegion* SphericalBoundingRegion::empty_ =
   new SphericalBoundingRegion(glm::vec3(0.0f), 0.0f);
