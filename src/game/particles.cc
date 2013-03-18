#include "particles.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


/*
static GLfloat colors[12][3]=  			// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};
*/

Particles::Particles(int id, Planet *planet) :
   active(true),
   life(1.0f),
   planet(planet),
   fade(float(rand()%100)/1000+0.003f),
  // direction(glm::vec3(float((rand()%50)-26.0f)*10.0f, float((rand()%50)-25.0f)*10.0f,float((rand()%50)-25.0f)*10.0f)),
   direction(glm::vec3(0.001, 0.1, 0.0)),
   gravity(glm::vec3(0.0f, 0.0f, 0.0f))
   //gravity(glm::vec3(0.0f, -0.8f, 0.0f))
   {
      std::ostringstream oss;
      oss << "bubbles" << id;
      
      float x = planet->center().x + float(.5 * rand()) / (RAND_MAX + 1.0);
      float y = planet->center().y + float(.5 * rand()) / (RAND_MAX + 1.0);
      center = glm::vec3(x, y, 0);
      
      new SceneNode("particle_container" +id);
      RootNode::Instance()->AddChild(SceneNode::Get("particle_container" + id));
      SceneNode::Get("particle_container" + id)->AddChild(SceneNode::Get(oss.str()));

   }

Particles::~Particles() {}

void Particles::Update(int id){
      // float slowdowns = 2.0;
      glColor4f(r, g, b, life);

      center.x += direction.x;
      center.y += direction.y;
      center.z += direction.z;

      if(center.x >= planet->center().x + .5 || center.y >= planet->center().y + planet->radius() + 3.0){
         center.x = planet->center().x + float(.5 * rand()) / (RAND_MAX + 1.0);
         center.y = planet->center().y + float(.5 * rand()) / (RAND_MAX + 1.0);
         // center.x = -4.2;
         // center.y = -1.7;
      }

      /*
      center.x += direction.x/(slowdowns*1000);
      center.y += direction.y/(slowdowns*1000);
      center.z += direction.z/(slowdowns*1000);
      */

      glm::mat4 transform;
      transform *= glm::translate(center);
      SceneNode::Get("particle_container" + id)->set_transformation(transform);

      /*direction.x += gravity.x;
      direction.y += gravity.y;
      direction.z += gravity.z;
      life -= fade;	*/

}
