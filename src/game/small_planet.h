#ifndef _SMALL_PLANET_H_
#define _SMALL_PLANET_H_

class SmallPlanet {
  public:

   const glm::vec3 &center() const { return center_; }
  private:
   glm::vec3 center_;
};

#endif
