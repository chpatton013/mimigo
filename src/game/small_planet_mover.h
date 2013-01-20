#ifndef SMALL_PLANET_MOVER_H_
#define SMALL_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "planet_rotater.h"

class SmallPlanetMover {
  public:
   SmallPlanetMover(Planet* planet, glm::vec3& position, Rotation& rotation);

   void MoveCounterClockwiseAroundPlanet();
   void MoveClockwiseAroundPlanet();
   void RotateBottomTowardPlanet();
   void StopMoving();
   void Jump();
   void Update();
   void set_planet(Planet* planet);

   bool IsTopSideOfPlanet() { return planet_rotater_->IsOnTopside(); }
   bool IsRightSideOfPlanet() { return planet_rotater_->IsOnRightside(); }
   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

  private:
   Planet* planet_;
   glm::vec3& position_;
   Rotation& rotation_;
   PlanetRotater* planet_rotater_;

   bool is_jumping_;
};

#endif
