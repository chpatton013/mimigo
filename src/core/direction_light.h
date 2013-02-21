#ifndef DIRECTION_LIGHT_H
#define DIRECTION_LIGHT_H

#include "core/light.h"

class DirectionLight : public Light {
  public:
   DirectionLight(const glm::vec3& color, const glm::vec4& position,
         const glm::vec4& direction) :
      Light(color, position, direction)
   {}
   virtual int type() const{ return kDirectionLight;}
};

#endif
