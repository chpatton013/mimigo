#ifndef ASSETS_H_
#define ASSETS_H_

#include <glm/glm.hpp>
#include <assert.h>
#include "util/glm_util.h"
#include <stdlib.h>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include "../spatial_hierarchy/collidable_entity.h"

class Planet;
class SceneNode;

class Assets : public CollidableEntity {
   public:
      Assets(){}
      Assets(const std::string& name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle, Planet* planet);
     // ~Assets();
     //void Move();
     bool BackAndForth(int begin, int end, float speed);
     bool UpAndDown(float max, float min, float speedup, float speedDown);
     bool Bounce();
     void UpdateMeshPosition();
     int type() {return 0;}
     glm::vec3 position();

   private:
      std::string name;
      glm::vec3 translate;
      glm::vec3 scale;
      glm::vec3 rotate;
      glm::vec3 position_;
      float theta_;
      SceneNode *mesh;
      Planet* planet;
      float rotateAngle;
      float up;
      bool flag;
      bool flag2;
      

      void Initialize(const std::string& name, const std::string& id);
      
};

#endif
