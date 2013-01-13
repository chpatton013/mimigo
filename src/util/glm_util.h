#ifndef GLM_UTIL_H
#define GLM_UTIL_H

#include "../../third_party/glm/glm/glm.hpp"
#include "../../third_party/glm/glm/gtc/type_ptr.hpp"
#include "../../third_party/glm/glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include <iostream>

namespace glm_util {

void Print(const glm::vec3& vec);
void Print(const glm::vec4& vec);
void Print(const glm::mat4& mat);
float magnitude(const glm::vec3& mat);

}

#endif
