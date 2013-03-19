#include "particleSys.h"
#include "core/mesh_load.h"

ParticleSystem::ParticleSystem(int num, Planet *planet, int move, std::string name) :
   amt(num),
   planet(planet)
{
   EntityComponent* particle_entity = LoadEntityComponentFromOBJ("meshes/star.obj", "textures/star_gold.bmp");
   EntityComponent* particle_entity1 = LoadEntityComponentFromOBJ("meshes/star.obj", "textures/star_yellow.bmp");
   EntityComponent* particle_entity2 = LoadEntityComponentFromOBJ("meshes/bee2.obj", "textures/bee2.bmp");
   
   EntityComponentNode* particle_mesh;

   for (int i = 0; i < num; i++) {
      std::ostringstream oss;
      oss << name << i;

      if(move == 0){
         printf("stars\n");
         if(i % 2 == 0){
            particle_mesh = new EntityComponentNode(oss.str(), particle_entity);
         }
         else {
            particle_mesh = new EntityComponentNode(oss.str(), particle_entity1);
         }
      }
      if(move == 1){
         printf("beees\n");
         particle_mesh = new EntityComponentNode(oss.str(), particle_entity2);
      }
      
      particle_mesh-> apply_transformation(glm::scale(glm::mat4(), glm::vec3(0.1f)));
      RootNode::Instance()->AddChild(particle_mesh);

      _particles.push_back(new Particles(i, planet, move, name));
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


