#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "bounding_region.h"
#include "spherical_bounding_region.h"
#include "axis_aligned_bounding_region.h"

namespace Collision {
   enum CollisionType {ADJACENT, INTERSECTING, SEPARATE, COLLISION_TYPE_COUNT};

   CollisionType CheckCollision(
         BoundingRegion* br1,
         BoundingRegion* br2
   );

   /**
    * Spherical collision functions.
    */
   CollisionType CheckCollisionSpherical(
         SphericalBoundingRegion* br1,
         BoundingRegion* br2
   );
   CollisionType CheckCollisionSphericalSpherical(
         SphericalBoundingRegion* br1,
         SphericalBoundingRegion* br2
   );
   CollisionType CheckCollisionSphericalAxisAligned(
         SphericalBoundingRegion* br1,
         AxisAlignedBoundingRegion* br2
   );

   /**
    * Axis-aligned collision functions.
    */
   CollisionType CheckCollisionAxisAligned(
         AxisAlignedBoundingRegion* br1,
         BoundingRegion* br2
   );
   CollisionType CheckCollisionAxisAlignedSpherical(
         AxisAlignedBoundingRegion* br1,
         SphericalBoundingRegion* br2
   );
   CollisionType CheckCollisionAxisAlignedAxisAligned(
         AxisAlignedBoundingRegion* br1,
         AxisAlignedBoundingRegion* br2
   );

   /**
    * Utility functions.
    */
   CollisionType ScalarBetween(float bound1, float bound2, float pt);
   CollisionType ScalarBetween(
         float bound1, float bound2, float pt, float delta
   );
   CollisionType PointBetween(
         const glm::vec3& bound1,
         const glm::vec3& bound2,
         const glm::vec3& pt
   );
   CollisionType PointBetween(
         const glm::vec3& bound1,
         const glm::vec3& bound2,
         const glm::vec3& pt,
         float delta
   );
}

#endif
