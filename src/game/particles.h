#include <glm/glm.hpp>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"
#include "planet.h"


class Planet; 
class SceneNode;

class Particles {
   public:
      Particles(glm::vec3 start, int id);
      ~Particles();
      void Update(int id);
      float r, g, b;
      glm::vec3 center;
      
   private:
      bool active;    
      float life;
      float fade;  
      
      glm::vec3 direction;
      glm::vec3 gravity;
     // float xi, yi, zi;
    //  float xg, yg, zg;
};
