#include <glm/glm.hpp>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"
#include "planet.h"
#include <sstream>


class Planet;
class SceneNode;

class Particles {
   public:
      Particles(int id, Planet *planet);
      ~Particles();
      void Update(int id);
      float r, g, b;
      glm::vec3 center;

   private:
      bool active;
      float life;
      float fade;
      Planet *planet;

      glm::vec3 direction;
      glm::vec3 gravity;
     // float xi, yi, zi;
    //  float xg, yg, zg;
};
