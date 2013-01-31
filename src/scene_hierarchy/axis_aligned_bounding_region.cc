#include "scene_hierarchy/axis_aligned_bounding_region.h"

AxisAlignedBoundingRegion* AxisAlignedBoundingRegion::empty_ =
   new AxisAlignedBoundingRegion(glm::vec3(0.0f), glm::vec3(0.0f));
