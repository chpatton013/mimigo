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
   void MoveBackward();
   void TurnLeft();
   void TurnRight();
   void StopMoving();
   void FallToPlanet();

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3 position() const;
   glm::mat4 local_axes() const { return local_axes_; }

  private:
   enum RotateType { ROTATE_LEFT, ROTATE_RIGHT, ROTATE_FORWARD, ROTATE_BACKWARD, ROTATE_NONE };
   void UpdateMeshTransform() const;
   void RotateBottomTowardPlanet();
   glm::vec3 local_x() {
      return glm::vec3(local_axes_[0][0], local_axes_[1][0], local_axes_[2][0]);
   }

   glm::vec3 local_y() {
      return glm::vec3(local_axes_[0][1], local_axes_[1][1], local_axes_[2][1]);
   }

   glm::vec3 local_z() {
      return glm::vec3(local_axes_[0][2], local_axes_[1][2], local_axes_[2][2]);
   }

   RotateType rotate_type_;

   Planet* planet_;
   float radius_;
   float theta_;
   float phi_;

   glm::mat4 local_axes_;

   float jump_speed_;
   bool is_jumping_;
   bool is_falling_;
   bool jump_held_;
};

#endif

