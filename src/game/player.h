#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "core/mesh_load.h"
#include "core/rotation.h"
#include "gl/gl_mesh.h"
#include "planet.h"
#include "planet_rotater.h"
#include "small_planet_mover.h"
#include "core/mover.h"
#include "scene_hierarchy/mesh_node.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"

class PlayerObserver {
  public:
   virtual void OnPlayerMove(const glm::vec3& where, const glm::vec3& up,
                             const glm::vec3& facing) = 0;
};

class Player {
  public:
   Player(Planet* planet);

   //Small Planet Motions
   void StartMovingUpAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingDownAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingLeftAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingRightAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StopMoving();
   //Small Planet Motions

   bool EntersGravityFieldOf(Planet* planet);
   void TransitionTo(Planet* planet);

   void Jump();

   void Update();
   bool is_jumping() const { return small_planet_mover_.is_jumping(); }

  private:
   void UpdateMeshTransform();
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();

   bool is_attached_to(Planet* planet) const
    { return small_planet_mover_.is_attached_to(planet); }

   SmallPlanetMover small_planet_mover_;

   glm::vec3 position_;
   Rotation xy_rotation_;
   Rotation xz_rotation_;
};

#endif
