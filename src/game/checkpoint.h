#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include <assert.h>
#include <string>
#include <glm/glm.hpp>
#include "../spatial_hierarchy/collidable_entity.h"

class Planet;
class SceneNode;

class CheckPoint : public CollidableEntity {
  public:
   CheckPoint() {}
   CheckPoint(Planet *planet, int planet_id, float theta, const std::string& id);
   virtual ~CheckPoint();
   bool Update();
   glm::vec3 position();

  int type(){return 1;}
  int planet(){return planet_id_;}
  int getTheta(){return theta_;}

  private:
   void UpdateMeshPosition();

   Planet* planet_;
   int planet_id_;
   float theta_;
   float radius_;

   SceneNode *mesh_;
};

#endif
