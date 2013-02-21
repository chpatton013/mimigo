#include <glm/glm.hpp>
#include "util/glm_util.h"
#include <stdlib.h>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"

class Assets{
   public:
      Assets(const std::string& name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle);
      ~Assets();

   private:
      std::string name;
      glm::vec3 translate;
      glm::vec3 scale;
      glm::vec3 rotate;
      float rotateAngle;

      void Initialize(const std::string& name, const std::string& id);
};
