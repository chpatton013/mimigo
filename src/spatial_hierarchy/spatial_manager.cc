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
 * Return an iterator to the firstCollidableEntity that `subject` collides with
 * in the range defined by `start` (inclusive) and `stop` (exclusive), or `stop`
 * if no intersection exists.
 *
 * Calling this iteratively until the return value equals `stop` will cover all
 * intersections in range, as `start` is incremented while assessing the range.
 *
 * WARNING: passing a subject that exists in the defined range results in a
 * self-collision.
 */
std::set<CollidableEntity*>::iterator SpatialManager::Collide(
   CollidableEntity* subject,
   std::set<CollidableEntity*>::iterator& start,
   std::set<CollidableEntity*>::iterator stop
) {
   for (
      BoundingRegion* subject_br = subject->bounding_region();
      (start != stop) && (Collision::CheckCollision(
         subject_br, (*start)->bounding_region()
      ) == Collision::SEPARATE);
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
