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

void SpatialManager::AddEntity(CollidableEntity* entity) {
   assert(entity != NULL);
   entities_.insert(entity);
   if (octree_ != NULL) {
      octree_->Add(entity);
   }
}
void SpatialManager::RemoveEntity(CollidableEntity* entity) {
   assert(entity != NULL);
   assert(entities_.find(entity) != entities_.end());
   entities_.erase(entity);
   if (octree_ != NULL) {
      octree_->Remove(entity);
   }
}

void SpatialManager::Establish(
   const glm::vec3& min_bound, const glm::vec3& max_bound
) {
   glm::vec3 min, max;
   GetBounds(&min, &max);

   min.x = std::min(min.x, min_bound.x);
   min.y = std::min(min.y, min_bound.y);
   min.z = std::min(min.z, min_bound.z);

   max.x = std::max(max.x, max_bound.x);
   max.y = std::max(max.y, max_bound.y);
   max.z = std::max(max.z, max_bound.z);

   if (octree_ == NULL) {
      octree_ = new Octree(entities_, min, max);
   }
}

/**
 * Return a set of CollidableEntities that `subject` collides with.
 */
std::set<CollidableEntity*> SpatialManager::Collide(CollidableEntity* subject) {
   return CollideOctree(subject);
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

std::set<CollidableEntity*> SpatialManager::CollideOctree(
   CollidableEntity* subject
) {
   return octree_->CollideEntity(subject);
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

void SpatialManager::GetBounds(glm::vec3* min, glm::vec3* max) {
   glm::vec3 running_min(FLT_MAX), running_max(FLT_MIN);

   for (std::set<CollidableEntity*>::iterator itr = entities_.begin();
         itr != entities_.end(); ++itr) {
      glm::vec3 current_min = (*itr)->bounding_region()->min();
      glm::vec3 current_max = (*itr)->bounding_region()->max();

      running_min.x = std::min(running_min.x, current_min.x);
      running_min.y = std::min(running_min.y, current_min.y);
      running_min.z = std::min(running_min.z, current_min.z);

      running_max.x = std::max(running_max.x, current_max.x);
      running_max.y = std::max(running_max.y, current_max.y);
      running_max.z = std::max(running_max.z, current_max.z);
   }

   *min = running_min;
   *max = running_max;
}
