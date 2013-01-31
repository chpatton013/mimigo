#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "bounding_region.h"
#include "spherical_bounding_region.h"
#include "axis_aligned_bounding_region.h"

// COLLISION_TYPE_COUNT __MUST__ be the last member of this enum.
enum CollisionType {ADJACENT, INTERSECTING, SEPARATE, COLLISION_TYPE_COUNT};

class Collision {
  public:
   static CollisionType CheckCollision(
         BoundingRegion& br1,
         BoundingRegion& br2
   );

  private:
   Collision();
   ~Collision();

   /**
    * Spherical collision functions.
    */
   static CollisionType CheckCollisionSpherical(
         SphericalBoundingRegion& br1,
         BoundingRegion& br2
   );
   static CollisionType CheckCollisionSphericalSpherical(
         SphericalBoundingRegion& br1,
         SphericalBoundingRegion& br2
   );
   static CollisionType CheckCollisionSphericalAxisAligned(
         SphericalBoundingRegion& br1,
         AxisAlignedBoundingRegion& br2
   ) {
      return PointBetween(
            br2.GetMin(), br2.GetMax(),
            br1.GetCenter(), br1.GetRadius()
      );
   }

   /**
    * Axis-aligned collision functions.
    */
   static CollisionType CheckCollisionAxisAligned(
         AxisAlignedBoundingRegion& br1,
         BoundingRegion& br2
   );
   static inline CollisionType CheckCollisionAxisAlignedSpherical(
         AxisAlignedBoundingRegion& br1,
         SphericalBoundingRegion& br2
   )
   { return CheckCollisionSphericalAxisAligned(br2, br1); }
   static CollisionType CheckCollisionAxisAlignedAxisAligned(
         AxisAlignedBoundingRegion& br1,
         AxisAlignedBoundingRegion& br2
   );

   /**
    * Utility functions.
    */
   static CollisionType ScalarBetween(float bound1, float bound2, float pt)
   { return ScalarBetween(bound1, bound2, pt, 0.0f); }
   static CollisionType ScalarBetween(
         float bound1, float bound2, float pt, float delta
   );
   static CollisionType PointBetween(
         const glm::vec3& bound1,
         const glm::vec3& bound2,
         const glm::vec3& pt
   )
   { return PointBetween(bound1, bound2, pt, 0.0f); }
   static CollisionType PointBetween(
         const glm::vec3& bound1,
         const glm::vec3& bound2,
         const glm::vec3& pt,
         float delta
   );
};

#endif
