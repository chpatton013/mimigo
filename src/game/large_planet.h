#ifndef LARGE_PLANET_H_
#define LARGE_PLANET_H_

#include "small_planet.h"

class LargePlanet : public SmallPlanet {
  public:
   LargePlanet(const std::string& id, const glm::vec3& center, float radius,
               float gravity_radius) :
      SmallPlanet(id, center, radius, gravity_radius)
   {}

   virtual bool is_small_planet() const { return false; }

  private:
};

#endif
