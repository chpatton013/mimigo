#ifndef LARGE_PLANET_H_
#define LARGE_PLANET_H_

#include "planet.h"

class LargePlanet : public Planet {
  public:
   LargePlanet(const std::string& id, const glm::vec3& center, float radius,
               float gravity_radius) :
      Planet(PLANET_TYPE_LARGE, id, center, radius, gravity_radius)
   {}
};

#endif
