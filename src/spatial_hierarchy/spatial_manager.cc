#include "spatial_manager.h"
#include "collision.h"

SpatialManager* SpatialManager::space_mgr_;

void SpatialManager::Update() {
   std::vector<CollidableEntity*> to_remove;
   for (std::set<CollidableEntity*>::iterator it = entities_.begin();
         it != entities_.end(); ++it) {
      if (!(*it)->Update()) {
         to_remove.push_back(*it);
      }
   }
   for (std::vector<CollidableEntity*>::iterator it = to_remove.begin();
         it != to_remove.end(); ++it) {
      RemoveEntity(*it);
      delete *it;
   }
}

/**
 * Return a set of CollidableEntities that `subject` collides with.
 */
std::set<CollidableEntity*> SpatialManager::Collide(CollidableEntity* subject) {
   return CollideComplete(subject);
}

std::set<CollidableEntity*> SpatialManager::CollideComplete(
   CollidableEntity* subject
) {
   std::set<CollidableEntity*>::iterator start = entities().begin(),
                                         stop = entities().end();
   std::set<CollidableEntity*> collisions;

   while (Collide(subject, start, stop) != stop) {
      collisions.insert(*(start++));
   }

   return collisions;
}

/**
 * Return an iterator to the first CollidableEntity that `subject` collides with
 * in the range defined by `start` (inclusive) and `stop` (exclusive), or `stop`
 * if no intersection exists.
 *
 * Calling this iteratively until the return value equals `stop` will cover all
 * intersections in range, as `start` is incremented while assessing the range.
 */
std::set<CollidableEntity*>::iterator SpatialManager::Collide(
   CollidableEntity* subject,
   std::set<CollidableEntity*>::iterator& start,
   std::set<CollidableEntity*>::iterator stop
) {
   for (
      BoundingRegion* subject_br = subject->bounding_region();
      (start != stop) && (
         *start != subject &&
         Collision::CheckCollision(
            subject_br, (*start)->bounding_region()
         ) == Collision::SEPARATE
      );
      ++start
   ) { /* I am a beautiful strong for-loop who don't need no body! */ }

   return start;
}

void SpatialManager::AddEntity(CollidableEntity* entity) {
   assert(entity != NULL);
   entities_.insert(entity);
}
void SpatialManager::RemoveEntity(CollidableEntity* entity) {
   assert(entity != NULL);
   assert(entities_.find(entity) != entities_.end());
   entities_.erase(entity);
}
