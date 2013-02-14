#ifndef SMALL_PLANET_MOVER_H_
#define SMALL_PLANET_MOVER_H_

#include <glm/glm.hpp>
#include "core/rotation.h"
#include "planet.h"
#include "core/timer.h"

class PlayerObserver;

class SmallPlanetMover : public Timer::Delegate {
  public:
   SmallPlanetMover(Planet* planet, PlayerObserver* observer);

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
   enum MoveType { CW, CCW, NONE };
   MoveType dir_facing_;
   MoveType move_dir_;
   void RotateBottomTowardPlanet();
   void UpdateMeshTransform() const;
   bool should_move_clockwise() const;
   bool should_move_counterclockwise() const;
   float max_theta_speed() const;
   void DetermineMovement();
   void set_theta(float theta);

   Planet* planet_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;

   float radius_;
   float jump_speed_;
   float theta_;
   float theta_speed_;

   bool is_jumping_;
   bool is_falling_;
   bool jump_held_;

   PlayerObserver* observer_;
};

#endif
