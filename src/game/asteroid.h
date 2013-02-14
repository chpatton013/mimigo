#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <assert.h>
#include <string>
#include <glm/glm.hpp>
#include "../spatial_hierarchy/collidable_entity.h"

class Planet;
class SceneNode;

class Asteroid : public CollidableEntity {
  public:
   Asteroid() {}
   Asteroid(Planet *planet, float theta, const std::string& id);
   virtual ~Asteroid();
   bool Update();
   glm::vec3 position();

  private:
   void UpdateMeshPosition();

   Planet* planet_;
   float theta_;
   float radius_;

   SceneNode *mesh_;
};

#endif
