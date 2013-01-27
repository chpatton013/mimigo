#ifndef SWING_ASTEROID_H_
#define SWING_ASTEROID_H_

#include <string>

class Planet;
class SceneNode;

class SwingAsteroid {
  public:
   SwingAsteroid(Planet *planet, float theta, const std::string& id);
   ~SwingAsteroid();
   bool Update();

  private:
   void UpdateMeshPosition();

   SceneNode *mesh_;

   Planet* planet_;
   float theta_;
   float radius_;
};

#endif
