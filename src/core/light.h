#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "global/handles.h"
#include "glm/glm.hpp"
#include "gl/GLSL_helper.h"

class Light {
  public:
   enum { kDirectionLight=0, kPointLight=1, kNormals=2 };
   Light(const glm::vec3& color, const glm::vec4& position,
         const glm::vec4& direction) :
      color_(color),
      position_(position),
      direction_(direction)
         {}

   void Draw() {
      float light[] = {
         color_.x, color_.y, color_.z, 0.0f,
         position_.x, position_.y, position_.z, 1.0f,
         direction_.x, direction_.y, direction_.z, 1.0f,
      };
      safe_glUniform4fv(g_handles["uLights"], 3, light);
      safe_glUniform1i(g_handles["uLightTypes"], type());
   }

   virtual int type() const = 0;

  protected:
   glm::vec3 color_;
   glm::vec4 position_;
   glm::vec4 direction_;
};

#endif
