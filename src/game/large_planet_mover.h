#ifndef LARGE_PLANET_MOVER_H_
#define LARGE_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "planet_rotater.h"

class LargePlanetMover {
  public:
   LargePlanetMover(Planet* planet);
   void set_planet(Planet* planet) {}

   void Jump() {}
   void Update();

   void MoveForward();
   void TurnLeft();
   void TurnRight();
   void StopMoving() {}

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3& position() const { return position_; }

  private:
   void UpdateMeshTransform() const;

   Planet* planet_;
   glm::vec3 position_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;
   PlanetRotater* planet_rotater_;

   bool is_jumping_;
};

#endif

