#ifndef _OCTREE_H_
#define _OCTREE_H_

#include <set>
#include <vector>
#include <glm/glm.hpp>
#include "axis_aligned_bounding_region.h"
#include "bounding_region.h"
#include "collidable_entity.h"
#include "collision.h"

class Octree {
  public:
   Octree(
      const glm::vec3& min_bound,
      const glm::vec3& max_bound,
      unsigned int max_depth = DFLT_MAX_DEPTH,
      unsigned int max_entities = DFLT_MAX_ENTITIES
   );
   Octree(
      const std::set<CollidableEntity*>& entities,
      const glm::vec3& min_bound,
      const glm::vec3& max_bound,
      unsigned int max_depth = DFLT_MAX_DEPTH,
      unsigned int max_entities = DFLT_MAX_ENTITIES
   );
   virtual ~Octree();

   virtual void Add(CollidableEntity* entity);
   virtual void Add(const std::set<CollidableEntity*>& entities);

   virtual void Remove(CollidableEntity* entity);
   virtual void Remove(const std::set<CollidableEntity*>& entities);

   virtual std::set<CollidableEntity*> CollideEntity(CollidableEntity* subject);

  private:
   static const unsigned int DFLT_MAX_DEPTH;
   static const unsigned int DFLT_MAX_ENTITIES;

   void Subdivide();
   int EntityCount();
   bool IsLeaf();
   bool IsDeep();
   bool IsFull();
   bool ContainsEntity(CollidableEntity* entity);
   void DeleteNodes();

   AxisAlignedBoundingRegion _aabr;

   const unsigned int _max_depth;
   const unsigned int _max_entities;

   std::vector<Octree*> _nodes;
   std::set<CollidableEntity*> _entities;
};

#endif
