#include <stdlib.h>
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include <vector>
#include <sstream>

class ParticleSystem {
   public: 
      ParticleSystem(int amt);
      ~ParticleSystem();
      void update();
      
  
   private:
      int amt;
      std::vector<Particles*> _particles;
};
