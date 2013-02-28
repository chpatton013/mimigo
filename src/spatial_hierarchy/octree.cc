#include "octree.h"

const unsigned int Octree::DFLT_MAX_DEPTH = 8;
const unsigned int Octree::DFLT_MAX_ENTITIES = 8;

Octree::Octree(
   const glm::vec3& min_bound,
   const glm::vec3& max_bound,
   unsigned int max_depth,
   unsigned int max_entities
) :
   _aabr(min_bound, max_bound),
   _max_depth(max_depth),
   _max_entities(max_entities)
{}
Octree::Octree(
   const std::set<CollidableEntity*>& entities,
   const glm::vec3& min_bound,
   const glm::vec3& max_bound,
   unsigned int max_depth,
   unsigned int max_entities
) :
   _aabr(min_bound, max_bound),
   _max_depth(max_depth),
   _max_entities(max_entities)
{
   Add(entities);
}
Octree::~Octree() {
   for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
         itr != _nodes.end(); ++itr) {
      if (*itr != NULL) {
         delete *itr;
      }
   }
}

void Octree::Add(CollidableEntity* entity) {
   // this tree alreadty subdivided: recurse to children
   if (!IsLeaf()) {
      for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
            itr != _nodes.end(); ++itr) {
         if (
            Collision::CheckCollision(
               &(*itr)->_aabr, entity->bounding_region()
            ) != Collision::SEPARATE
         ) {
            (*itr)->Add(entity);
         }
      }
   // this tree is a maximum-depth leaf or a partially-filled leaf: insert here
   } else if (IsDeep() || !IsFull()) {
      _entities.insert(entity);
   // this leaf is full: construct children and recurse to self
   } else {
      // create children
      Subdivide();

      // re-parent entities
      Add(_entities);
      _entities.clear();

      // recurse
      Add(entity);
   }
}
void Octree::Add(const std::set<CollidableEntity*>& entities) {
   for (std::set<CollidableEntity*>::const_iterator itr = entities.begin();
         itr != entities.end(); ++itr) {
      Add(*itr);
   }
}

void Octree::Remove(CollidableEntity* entity) {
   if (!IsLeaf()) {
      int entity_count = 0;

      // remove entity from child nodes
      for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
            itr != _nodes.end(); ++itr) {
         (*itr)->Remove(entity);
         entity_count += (*itr)->EntityCount();
      }

      // delete child nodes if all empty
      if (entity_count == 0) {
         DeleteNodes();
      }
   // remove entity from self
   } else if (ContainsEntity(entity)) {
      _entities.erase(entity);
   }
}
void Octree::Remove(const std::set<CollidableEntity*>& entities) {
   for (std::set<CollidableEntity*>::const_iterator itr = entities.begin();
         itr != entities.end(); ++itr) {
      Remove(*itr);
   }
}

std::set<CollidableEntity*> Octree::CollideEntity(CollidableEntity* subject) {
   std::set<CollidableEntity*> collisions;

   if (IsLeaf()) {
      for (std::set<CollidableEntity*>::const_iterator itr = _entities.begin();
            itr != _entities.end(); ++itr) {
         if (
            Collision::CheckCollision(
               (*itr)->bounding_region(), subject->bounding_region()
            ) != Collision::SEPARATE
         ) {
            collisions.insert(*itr);
         }
      }
   } else {
      for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
            itr != _nodes.end(); ++itr) {
         if (
            Collision::CheckCollision(
               &(*itr)->_aabr, subject->bounding_region()
            ) != Collision::SEPARATE
         ) {
            std::set<CollidableEntity*> child_collisions =
             (*itr)->CollideEntity(subject);

            collisions.insert(child_collisions.begin(), child_collisions.end());
         }
      }
   }

   return collisions;
}

void Octree::Subdivide() {
   unsigned int next_depth = _max_depth - 1;
   glm::vec3 min = _aabr.min();
   glm::vec3 max = _aabr.max();
   glm::vec3 mid = _aabr.center();

   _nodes.push_back(new Octree(min, mid, next_depth, _max_entities));
   _nodes.push_back(new Octree(
      glm::vec3(min.x, min.y, mid.z), glm::vec3(mid.x, mid.y, max.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(
      glm::vec3(mid.x, min.y, min.z), glm::vec3(max.x, mid.y, mid.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(
      glm::vec3(mid.x, min.y, mid.z), glm::vec3(max.x, mid.y, max.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(
      glm::vec3(min.x, mid.y, min.z), glm::vec3(mid.x, max.y, mid.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(
      glm::vec3(mid.x, mid.y, min.z), glm::vec3(max.x, max.y, mid.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(
      glm::vec3(min.x, mid.y, mid.z), glm::vec3(mid.x, max.y, max.z),
      next_depth, _max_entities
   ));
   _nodes.push_back(new Octree(mid, max, next_depth, _max_entities));
}

int Octree::EntityCount() {
   int entity_count = _entities.size();

   for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
         itr != _nodes.end(); ++itr) {
      entity_count += (*itr)->EntityCount();
   }

   return entity_count;
}

bool Octree::IsLeaf() {
   return _nodes.empty();
}

bool Octree::IsDeep() {
   return _max_depth == 0;
}

bool Octree::IsFull() {
   return _entities.size() >= _max_entities;
}

bool Octree::ContainsEntity(CollidableEntity* entity) {
   return _entities.find(entity) != _entities.end();
}

void Octree::DeleteNodes() {
   for (std::vector<Octree*>::const_iterator itr = _nodes.begin();
         itr != _nodes.end(); ++itr) {
      if (*itr != NULL) {
         delete *itr;
      }
   }
   _nodes.clear();
}
