#ifndef _SMALL_PLANET_H_
#define _SMALL_PLANET_H_

class SmallPlanet {
  public:
   //const glm::vec3 &center() const { return center_; }
   //float radius() const { return radius_; }

   const glm::vec3 center() const { return glm::vec3(0.0f); }
   float radius() const { return 1.0f; }

  private:
   glm::vec3 center_;
   float radius_;
};

#endif
