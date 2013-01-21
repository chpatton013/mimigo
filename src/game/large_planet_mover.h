#ifndef LARGE_PLANET_MOVER_H_
#define LARGE_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "planet_rotater.h"

class LargePlanetMover {
  public:
   LargePlanetMover(Planet* planet);
   void set_planet(Planet* planet);

   void Jump() {}
   void Update();

   void MoveForward();
   void TurnLeft();
   void TurnRight();
   void StopMoving();
   void FallToPlanet();

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3 position() const;

  private:
   enum RotateType { ROTATE_LEFT, ROTATE_RIGHT, ROTATE_NONE };
   void UpdateMeshTransform() const;
   void RotateBottomTowardPlanet();

   RotateType rotate_type_;

   Planet* planet_;
   float radius_;
   float theta_;
   float phi_;

   Rotation xy_rotation_;
   Rotation xz_rotation_;

   float jump_speed_;
   bool is_jumping_;
   bool is_falling_;
   bool jump_held_;
};

#endif

