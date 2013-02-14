#include "collision.h"

#include <algorithm>
#include <glm/glm.hpp>

Collision::CollisionType Collision::CheckCollision(
      BoundingRegion* br1,
      BoundingRegion* br2
) {
   if (br1 == NULL || br2 == NULL) {
      return SEPARATE;
   }

   SphericalBoundingRegion* br1_sp =
    dynamic_cast<SphericalBoundingRegion*>(br1);
   if (br1_sp != NULL) {
      return CheckCollisionSpherical(br1_sp, br2);
   }

   AxisAlignedBoundingRegion* br1_aa =
    dynamic_cast<AxisAlignedBoundingRegion*>(br1);
   if (br1_aa != NULL) {
      return CheckCollisionAxisAligned(br1_aa, br2);
   }

   return SEPARATE;
}

Collision::CollisionType Collision::CheckCollisionSpherical(
      SphericalBoundingRegion* br1,
      BoundingRegion* br2
) {
   SphericalBoundingRegion* br2_sp =
    dynamic_cast<SphericalBoundingRegion*>(br2);
   if (br2_sp != NULL) {
      return CheckCollisionSphericalSpherical(br1, br2_sp);
   }

   AxisAlignedBoundingRegion* br2_aa =
    dynamic_cast<AxisAlignedBoundingRegion*>(br2);
   if (br2_aa != NULL) {
      return CheckCollisionSphericalAxisAligned(br1, br2_aa);
   }

   return SEPARATE;
}
Collision::CollisionType Collision::CheckCollisionSphericalSpherical(
      SphericalBoundingRegion* br1,
      SphericalBoundingRegion* br2
) {
   glm::vec3 c1 = br1->center(),
             c2 = br2->center();
   float r1 = br1->radius(),
         r2 = br2->radius();
   float dx = c1.x - c2.x,
         dy = c1.y - c2.y,
         dz = c1.z - c2.z;
   float dist = dx * dx + dy * dy + dz * dz;
   float res = dist - (r1 + r2) * (r1 + r2);

   if (res < 0.0f) {
      return INTERSECTING;
   } else if (res > 0.0f) {
      return SEPARATE;
   } else {
      return ADJACENT;
   }
}
Collision::CollisionType Collision::CheckCollisionSphericalAxisAligned(
      SphericalBoundingRegion* br1,
      AxisAlignedBoundingRegion* br2
) {
   return PointBetween(br2->min(), br2->max(), br1->center(), br1->radius());
}

Collision::CollisionType Collision::CheckCollisionAxisAligned(
      AxisAlignedBoundingRegion* br1,
      BoundingRegion* br2
) {
   SphericalBoundingRegion* br2_sp =
    dynamic_cast<SphericalBoundingRegion*>(br2);
   if (br2_sp != NULL) {
      return CheckCollisionAxisAlignedSpherical(br1, br2_sp);
   }

   AxisAlignedBoundingRegion* br2_aa =
    dynamic_cast<AxisAlignedBoundingRegion*>(br2);
   if (br2_aa != NULL) {
      return CheckCollisionAxisAlignedAxisAligned(br1, br2_aa);
   }

   return SEPARATE;
}
Collision::CollisionType Collision::CheckCollisionAxisAlignedSpherical(
      AxisAlignedBoundingRegion* br1,
      SphericalBoundingRegion* br2
) {
   return CheckCollisionSphericalAxisAligned(br2, br1);
}
Collision::CollisionType Collision::CheckCollisionAxisAlignedAxisAligned(
      AxisAlignedBoundingRegion* br1,
      AxisAlignedBoundingRegion* br2
) {
   const glm::vec3& min1 = br1->min();
   const glm::vec3& max1 = br1->max();
   const glm::vec3& min2 = br2->min();
   const glm::vec3& max2 = br2->max();
   float x1 = min2.x, y1 = min2.y, z1 = min2.z,
         x2 = max2.x, y2 = max2.y, z2 = max2.z;
   glm::vec3 pt;

   char counters[(int)COLLISION_TYPE_COUNT];
   for (int ndx = 0; ndx < (int)COLLISION_TYPE_COUNT; ++ndx) {
      counters[ndx] = 0;
   }

   // glm::vec3(x1, y1, z1);
   ++counters[(int)PointBetween(min1, max1, min2)];

   pt = glm::vec3(x1, y1, z2);
   ++counters[(int)PointBetween(min1, max1, pt)];

   pt = glm::vec3(x1, y2, z1);
   ++counters[(int)PointBetween(min1, max1, pt)];

   pt = glm::vec3(x1, y2, z2);
   ++counters[(int)PointBetween(min1, max1, pt)];

   pt = glm::vec3(x2, y1, z1);
   ++counters[(int)PointBetween(min1, max1, pt)];

   pt = glm::vec3(x2, y1, z2);
   ++counters[(int)PointBetween(min1, max1, pt)];

   pt = glm::vec3(x2, y2, z1);
   ++counters[(int)PointBetween(min1, max1, pt)];

   // glm::vec3(x2, y2, z2);
   ++counters[(int)PointBetween(min1, max1, max2)];

   if (counters[INTERSECTING] > 0) {
      return INTERSECTING;
   } else if (counters[ADJACENT] > 0) {
      if (counters[ADJACENT] < 8) {
         return ADJACENT;
      } else {
         return INTERSECTING;
      }
   } else {
      return SEPARATE;
   }
}

Collision::CollisionType Collision::ScalarBetween(
      float bound1, float bound2, float pt
) {
   return ScalarBetween(bound1, bound2, pt, 0.0f);
}
Collision::CollisionType Collision::ScalarBetween(
      float bound1, float bound2, float pt, float delta
) {
   float b_min = std::min(bound1, bound2);
   float b_max = std::max(bound1, bound2);

   if (pt > b_min - delta) {
      if (pt > b_max + delta) {
         return SEPARATE;
      } else if (pt < b_max + delta) {
         return INTERSECTING;
      } else {
         return ADJACENT;
      }
   } else if (pt < b_min - delta) {
      return SEPARATE;
   } else {
      return ADJACENT;
   }
}
Collision::CollisionType Collision::PointBetween(
      const glm::vec3& bound1,
      const glm::vec3& bound2,
      const glm::vec3& pt
) {
   return PointBetween(bound1, bound2, pt, 0.0f);
}
Collision::CollisionType Collision::PointBetween(
      const glm::vec3& bound1,
      const glm::vec3& bound2,
      const glm::vec3& pt,
      float delta
) {
   char counters[(int)COLLISION_TYPE_COUNT];
   for (int ndx = 0; ndx < (int)COLLISION_TYPE_COUNT; ++ndx) {
      counters[ndx] = 0;
   }

   ++counters[ScalarBetween(bound1.x, bound2.x, pt.x, delta)];
   ++counters[ScalarBetween(bound1.y, bound2.y, pt.y, delta)];
   ++counters[ScalarBetween(bound1.z, bound2.z, pt.z, delta)];

   if (counters[SEPARATE] > 0) {
      return SEPARATE;
   } else if (counters[ADJACENT] > 0) {
      return ADJACENT;
   } else {
      return INTERSECTING;
   }
}
