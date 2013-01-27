#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <string>

class Planet;
class SceneNode;

class Asteroid {
  public:
   Asteroid(Planet *planet, float theta, const std::string& id);
   ~Asteroid();
   bool Update();

  private:
   void UpdateMeshPosition();

   SceneNode *mesh_;

   Planet* planet_;
   float theta_;
   float radius_;
};

#endif