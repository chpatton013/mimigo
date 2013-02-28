#ifndef _SPATIAL_MANAGER_H_
#define _SPATIAL_MANAGER_H_

#include <set>
#include "bounding_region.h"
#include "collidable_entity.h"

class SpatialManager {
  public:
   static SpatialManager* Instance() {
      if (!space_mgr_) {
         space_mgr_ = new SpatialManager();
      }
      return space_mgr_;
   }

   virtual void Update();

   virtual std::set<CollidableEntity*> Collide(CollidableEntity* subject);
   virtual std::set<CollidableEntity*>::iterator Collide(
      CollidableEntity* subject,
      std::set<CollidableEntity*>::iterator& start,
      std::set<CollidableEntity*>::iterator stop
   );

   virtual void AddEntity(CollidableEntity* entity);
   virtual void RemoveEntity(CollidableEntity* entity);

   virtual const std::set<CollidableEntity*>& entities() const {
      return entities_;
   }

  private:
   static SpatialManager* space_mgr_;
   SpatialManager() {}
   virtual ~SpatialManager() {}

   std::set<CollidableEntity*> CollideComplete(CollidableEntity* subject);

   std::set<CollidableEntity*> entities_;
};

#endif
