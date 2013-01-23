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
   void MoveLeft();
   void MoveRight();

   void StopMoveUp();
   void StopMoveDown();
   void StopMoveLeft();
   void StopMoveRight();

   bool is_attached_to(Planet* planet) const { return planet_ == planet; }
   bool is_jumping() const { return is_jumping_; }

   const glm::vec3 position() const;

   virtual void OnExpiration(const std::string& event);

  private:
   enum Dir { UP=1, DOWN=1<<1, LEFT=1<<2, RIGHT=1<<3 };
   void RotateBottomTowardPlanet();
   void UpdateMeshTransform() const;

   Planet* planet_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;

   float radius_;
   float jump_speed_;
   float theta_;
   float theta_speed_;
   unsigned short move_dir_;

   bool is_jumping_;
   bool is_falling_;
   bool jump_held_;
};

#endif
