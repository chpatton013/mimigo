#ifndef _COLLIDABLE_ENTITY_H_
#define _COLLIDABLE_ENTITY_H_

#include "../core/entity.h"
#include "bounding_region.h"

class CollidableEntity : public Entity {
  public:
   CollidableEntity();
   CollidableEntity(BoundingRegion* br);
   virtual ~CollidableEntity();

   virtual int type() = 0;

   BoundingRegion* bounding_region();
   BoundingRegion* set_bounding_region(BoundingRegion* br);

  protected:
   BoundingRegion* bounding_region_;
};

#endif
