#include "particles.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

Particles::Particles(int id, Planet *planet, int moves, std::string name) :
   active(true),
   life(1.0f),
   planet(planet),
   fade(float(rand()%100)/1000+0.003f),
   angle(float(rand() % 360)),
   move(moves),
   
  // direction(glm::vec3(float((rand()%50)-26.0f)*10.0f, float((rand()%50)-25.0f)*10.0f,float((rand()%50)-25.0f)*10.0f)),
   direction(glm::vec3(0.001, 0.1, 0.0)),
   gravity(glm::vec3(0.0f, 0.0f, 0.0f))
   //gravity(glm::vec3(0.0f, -0.8f, 0.0f))
   {
      std::ostringstream oss;
      oss << name << id;
      
      std::ostringstream pc;
      pc << "particle" << name << id;
      pc_ = pc.str();

      if(move == 0){
         CircleSetup();
      }
      if(move == 1){
         BeeSetup();
      }
      new SceneNode(pc_);
      RootNode::Instance()->AddChild(SceneNode::Get(pc_));
      SceneNode::Get(pc_)->AddChild(SceneNode::Get(oss.str()));

   }
   
void Particles::CircleSetup(){
   radius = (float)rand() / ((float)RAND_MAX / (0.3));
   float x = planet->center().x + radius * cos(angle);
   float y = 1.5 + (float)rand() / ((float)RAND_MAX / (1.8 - 1.5));
   float z = planet->center().z + radius * sin(angle);
   
      
   center = glm::vec3(x, planet->center().y + planet->radius() + y, z);
}

void Particles::BeeSetup(){
   HI = 1.5;
   LO = .8;
   direction = glm::vec3(-1, -1, 0);
   float x = (float)rand() / ((float)RAND_MAX / (1));
   float y = LO + (float)rand() / ((float)RAND_MAX / (HI - LO));
   float z = -.3 + (float)rand() / ((float)RAND_MAX / (.3 + .3));
   flag = true;
   
   center = glm::vec3(x + planet->center().x, planet->center().y + planet->radius() + y, z);
}

Particles::~Particles() {}

void Particles::Update(int id){
      // float slowdowns = 2.0;
      glColor4f(r, g, b, life);
      
      if(move == 0){
         CircleUpdate();
      }
      if(move == 1){
         BeeUpdate();
      }
      glm::mat4 transform;
      transform *= glm::translate(center);
      SceneNode::Get(pc_)->set_transformation(transform);


}

void Particles::CircleUpdate(){
   angle++;
   if(angle > 360){
      angle = 0;
   }
      
   center.x = planet->center().x + radius * cos(angle);
   center.z = planet->center().z + radius * sin(angle);
}

void Particles::BeeUpdate(){
   center.x += (float)rand() / ((float)RAND_MAX / .05);
   
   if(center.y > planet->center().y + planet->radius() + HI){
      flag = false;
   }
   else if (center.y < planet->center().y + planet->radius() + LO){
      flag = true;
   }
   if(flag){
      //center.y += .05;
      center.y += (float)rand() / ((float)RAND_MAX / (.05));
   }
   else {
      //center.y -= .05;
      center.y -= (float)rand() / ((float)RAND_MAX / (.05));
   }  
}
