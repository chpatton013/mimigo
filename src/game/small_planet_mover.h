#ifndef SMALL_PLANET_MOVER_H_
#define SMALL_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "planet_rotater.h"
#include "core/timer.h"

class SmallPlanetMover : public Timer::Delegate {
  public:
   SmallPlanetMover(Planet* planet);

   void StopMoving();
   void Jump();
   void ReleaseJump();
   void Update();
   void set_planet(Planet* planet);

   void FallToPlanet();

   void MoveUp();
   void MoveDown();
   void MoveLeft(const glm::vec3& camera_pos);
   void MoveRight(const glm::vec3& camera_pos);

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3 position() const;

   virtual void OnExpiration(const std::string& event);

  private:
   enum RotateType { ROTATE_CW, ROTATE_CCW, ROTATE_NONE };
   void RotateBottomTowardPlanet();
   void UpdateMeshTransform() const;
   void MoveCounterClockwiseAroundPlanet();
   void MoveClockwiseAroundPlanet();

   Planet* planet_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;

   float radius_;
   float jump_speed_;
   RotateType rotate_type_;
   float theta_;
   float theta_speed_;

   bool is_jumping_;
   bool is_falling_;
   bool jump_held_;
};

#endif
