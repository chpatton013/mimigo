#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "core/mesh_load.h"
#include "core/rotation.h"
#include "gl/gl_mesh.h"
#include "planet.h"
#include "planet_rotater.h"
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

   void StartMovingUpAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingDownAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingLeftAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StartMovingRightAroundAttachedPlanet(const glm::vec3& camera_pos);
   void StopMoving();

   bool EntersGravityFieldOf(Planet* planet);

   void Jump();

   void attach_planet(Planet* planet) {
      attached_planet_ = planet;
      planet_rotater_ = PlanetRotater(planet->center(), planet->radius(),
            position_);
   }

   void TransitionTo(Planet* planet);

   void Update();

   static void RotationEndCallback(void* player);

   void register_observer(PlayerObserver* observer) {
      observer_ = observer;
   }

   glm::vec3 up() const;
   glm::vec3 facing() const;

  private:
   void UpdateMesh();
   void RotateBottomToward(Planet* planet);
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();
   bool IsTopSideOfPlanet();
   bool IsRightSideOfPlanet();

   bool is_jumping() const { return is_jumping_; }

   SceneNode* mesh_;
   Planet* attached_planet_;
   Planet* transition_planet_;
   PlanetRotater planet_rotater_;

   Rotater rotater_;

   glm::vec3 position_;
   Rotation rotation_;
   Rotation left_right_rotation_;
   bool is_jumping_;

   PlayerObserver* observer_;
};

#endif
