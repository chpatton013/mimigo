#ifndef LARGE_PLANET_MOVER_H_
#define LARGE_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"

class LargePlanetMover {
  public:
   LargePlanetMover(Planet* planet);

   void Jump();
   void Update();

   void set_planet(Planet* planet);
   void MoveForward();
   void MoveBackward();
   void TurnLeft();
   void TurnRight();
   void StopMoveForward();
   void StopMoveBackward();
   void StopTurnLeft();
   void StopTurnRight();

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3 position() const;
   const glm::vec3 forward() const;
   const glm::vec3 right() const;
   const glm::vec3 up() const;

   glm::mat4 local_rotation() const { return local_rotation_; }

  private:
   void UpdateMeshTransform() const;
   void RotateBottomTowardPlanet();

   Planet* planet_;

   glm::mat4 local_rotation_;
   glm::mat4 transform_;
   glm::vec3 position_;
   float angle_speed_;
   float rotate_speed_;

   bool move_forward_;
   bool move_backward_;
   bool turn_left_;
   bool turn_right_;

   float jump_speed_;
   bool is_jumping_;
   bool jump_held_;
};

#endif

