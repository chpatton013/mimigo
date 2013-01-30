#include "glm_util.h"

namespace glm_util {
using namespace glm;

void Print(const vec3& vec) {
   std::cout << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">"
      << std::endl;
}

void Print(const vec4& vec) {
   std::cout << "<" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w
      << ">" << std::endl;
}

void Print(const mat4& mat) {
   for (size_t r = 0; r < 4; ++r) {
      for (size_t c = 0; c < 4; ++c) {
         if (std::abs(mat[c][r]) < 1e-7)
            std::cout << "0, ";
         else
            std::cout << mat[c][r] << ", ";
      }
      std::cout << std::endl;
   }
}

float magnitude(const glm::vec3& v) {
   return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
}
