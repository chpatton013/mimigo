#include <glm/glm.hpp>
#include "util/glm_util.h"
#include "planet.h"
#include <stdlib.h>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"

class Assets {
   public:
      Assets(const std::string& name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle, Planet* planet);
     // ~Assets();
     //void Move();
     bool BackAndForth(int begin, int end, float speed);
     bool UpAndDown(float max, float min, float speedup, float speedDown);
     bool Bounce();
     void UpdateMeshPosition();

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
