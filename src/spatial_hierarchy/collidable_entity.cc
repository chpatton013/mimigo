#include "collidable_entity.h"

CollidableEntity::CollidableEntity() :
   bounding_region_(NULL)
{}
CollidableEntity::CollidableEntity(BoundingRegion* br) :
   bounding_region_(br)
{}
CollidableEntity::~CollidableEntity() {
   if (bounding_region_ != NULL) {
      delete bounding_region_;
   }
}

BoundingRegion* CollidableEntity::bounding_region() {
   return bounding_region_;
}
BoundingRegion* CollidableEntity::set_bounding_region(BoundingRegion* br) {
   BoundingRegion* old_br = bounding_region_;
   bounding_region_ = br;
   return old_br;
}
