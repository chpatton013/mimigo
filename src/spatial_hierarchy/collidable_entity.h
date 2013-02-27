#ifndef _COLLIDABLE_ENTITY_H_
#define _COLLIDABLE_ENTITY_H_

#include "../core/entity.h"
#include "bounding_region.h"

class CollidableEntity : public Entity {
  public:
   CollidableEntity() :
      bounding_region_(NULL)
   {}
   CollidableEntity(BoundingRegion* br) :
      bounding_region_(br)
   {}
   virtual ~CollidableEntity() {
      if (bounding_region_ != NULL) {
         delete bounding_region_;
      }
   }

  virtual int type() = 0;
 virtual int planet() = 0;

   BoundingRegion* bounding_region() { return bounding_region_; }
   BoundingRegion* set_bounding_region(BoundingRegion* br) {
      BoundingRegion* old_br = bounding_region_;
      bounding_region_ = br;
      return old_br;
   }

  protected:
   BoundingRegion* bounding_region_;
};

#endif
