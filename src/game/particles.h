#include <glm/glm.hpp>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"
#include "planet.h"
#include <sstream>


class Planet;
class SceneNode;

class Particles {
   public:
      Particles(int id, Planet *planet, int move, std::string);
      ~Particles();
      void Update(int id);
      void SetCircle();
      void CircleUpdate(int id);
      float r, g, b;
      float radius;
      glm::vec3 center;

   private:
      bool active;
      float life;
      float fade;
      float angle;
      int move;
      bool flag;
      
      int HI;
      int LO;
      
      Planet *planet;
      void CircleSetup();
      void CircleUpdate();
      
      void BeeSetup();
      void BeeUpdate();
      
      std::string pc_;

      glm::vec3 direction;
      glm::vec3 gravity;
     // float xi, yi, zi;
    //  float xg, yg, zg;
};
