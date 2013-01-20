#ifndef SMALL_PLANET_H_
#define SMALL_PLANET_H_

#include "planet.h"

class SmallPlanet : public Planet {
  public:
   SmallPlanet(const std::string& id, const glm::vec3& center, float radius,
               float gravity_radius) :
      Planet(PLANET_TYPE_SMALL, id, center, radius, gravity_radius)
   {}
};

#endif
