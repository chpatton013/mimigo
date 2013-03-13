#include "particleSys.h"
#include "core/mesh_load.h"

ParticleSystem::ParticleSystem(int num, Planet *planet) :
   amt(num),
   planet(planet)
{
   EntityComponent* particle_entity = LoadEntityComponentFromOBJ("meshes/sphere.obj", "textures/earth1.bmp");

   for (int i = 0; i < num; i++) {
      std::ostringstream oss;
      oss << "bubbles" << i;

      EntityComponentNode* particle_mesh = new EntityComponentNode(oss.str(), particle_entity);
      particle_mesh-> apply_transformation(glm::scale(glm::mat4(), glm::vec3(0.1f)));
      RootNode::Instance()->AddChild(particle_mesh);

      _particles.push_back(new Particles(i, planet));
   }
}

void ParticleSystem::update(){
   int id = 0;
   for(std::vector<Particles*>::iterator it = _particles.begin();
         it != _particles.end(); ++it){
      (*it)->Update(id);
      ++id;
   }
}


