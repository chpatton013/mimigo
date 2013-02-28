#ifndef SWING_ASTEROID_H_
#define SWING_ASTEROID_H_

#include <assert.h>
#include <string>
#include <glm/glm.hpp>
#include "small_planet_mover.h"
#include "../spatial_hierarchy/collidable_entity.h"

class Planet;
class SceneNode;

class SwingAsteroid : public CollidableEntity {
  public:
   SwingAsteroid() {}
   SwingAsteroid(Planet *planet, float theta, const std::string& id, bool cw);
   virtual ~SwingAsteroid();
   bool Update();
   glm::vec3 position() { return position_; }

   int type(){ return 0;}
  private:
   void UpdateMeshPosition();

   bool planetary_motion_;
   Planet* planet_;
   glm::vec3 position_;
   float theta_;
   bool cw_;

   SceneNode *mesh_;
};

#endif
