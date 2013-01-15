#ifndef GLM_UTIL_H
#define GLM_UTIL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace glm_util {

void Print(const glm::vec3& vec);
void Print(const glm::vec4& vec);
void Print(const glm::mat4& mat);
float magnitude(const glm::vec3& mat);

}

#endif
