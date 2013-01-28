#ifndef SWING_ASTEROID_H_
#define SWING_ASTEROID_H_

#include <string>
#include <glm/glm.hpp>
#include "small_planet_mover.h"

class Planet;
class SceneNode;

class SwingAsteroid {
  public:
   SwingAsteroid(Planet *planet, float theta, const std::string& id);
   ~SwingAsteroid();
   bool Update();

  private:
   void UpdateMeshPosition();

   bool planetary_motion_;
   Planet* planet_;
   glm::vec3 position_;
   float theta_;

   SceneNode *mesh_;
};

#endif
