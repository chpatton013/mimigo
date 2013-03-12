#include <stdlib.h>
#include "particles.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include <vector>
#include <sstream>

class ParticleSystem {
  public:
   ParticleSystem(int amt, Planet *planet);
   ~ParticleSystem();
   void update();

  private:
   int amt;
   Planet *planet;
   std::vector<Particles*> _particles;
};
