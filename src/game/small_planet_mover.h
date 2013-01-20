#ifndef SMALL_PLANET_MOVER_H_
#define SMALL_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "planet_rotater.h"

class SmallPlanetMover {
  public:
   SmallPlanetMover(Planet* planet);

   void StopMoving();
   void Jump();
   void Update();
   void set_planet(Planet* planet);

   void MoveForward();
   void TurnLeft();
   void TurnRight();

   void MoveUp(const glm::vec3& camera_pos);
   void MoveDown(const glm::vec3& camera_pos);
   void MoveLeft(const glm::vec3& camera_pos);
   void MoveRight(const glm::vec3& camera_pos);

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3& position() const { return position_; }

  private:
   void RotateBottomTowardPlanet();
   void UpdateMeshTransform() const;
   void MoveCounterClockwiseAroundPlanet();
   void MoveClockwiseAroundPlanet();
   bool IsTopSideOfPlanet() { return planet_rotater_->IsOnTopside(); }
   bool IsRightSideOfPlanet() { return planet_rotater_->IsOnRightside(); }

   Planet* planet_;
   glm::vec3 position_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;
   PlanetRotater* planet_rotater_;

   bool is_jumping_;
};

#endif
