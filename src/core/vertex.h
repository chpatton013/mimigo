#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include "../core/material.h"

/* all the *attributes* needed by a vertex in the vertex shader. */

struct Vertex {
   Vertex(const glm::vec4 position=glm::vec4()) :
      ambient(glm::vec3(0.9, 0.9, 0.9)),
      diffuse(glm::vec3(0.9, 0.9, 0.9)),
      specular(glm::vec3(0.9, 0.9, 0.9)),
      position(position)
   {}
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
   glm::vec3 normal;
   glm::vec4 position;
   glm::vec2 texture;

   void set_material(const Material& material) {
      diffuse = material.kDiffuse;
      ambient = material.kAmbient;
      specular = material.kSpecular;
   }

   operator glm::vec4& () { return position; }
   float x() { return position.x; }
   float y() { return position.y; }
   float z() { return position.z; }
};

#endif
