#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../../third_party/glm/glm/glm.hpp"

struct Material {
   glm::vec3 kDiffuse;
   glm::vec3 kAmbient;
   glm::vec3 kSpecular;
   std::string name;
};

#endif
