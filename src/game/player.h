#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "small_planet_mover.h"
#include "large_planet_mover.h"
#include "universe.h"
#include "planet.h"
#include "../core/entity.h"
#include "../core/mesh_load.h"
#include "../core/rotation.h"
#include "../core/mover.h"
#include "../gl/gl_mesh.h"
#include "../scene_hierarchy/root_node.h"
#include "../scene_hierarchy/scene_node.h"
#include "../spatial_hierarchy/collidable_entity.h"

class PlayerObserver {
  public:
   virtual void OnPlayerMove(const glm::vec3& where, const glm::vec3& up,
                             const glm::vec3& facing) = 0;
   virtual void OnPlayerSwitchPlanets(Planet* planet) = 0;
};

class Player : public CollidableEntity {
  public:
   Player(Planet* planet, PlayerObserver* observer);
   virtual ~Player() {}

   void OnUpButtonDown();
   void OnDownButtonDown();
   void OnLeftButtonDown();
   void OnRightButtonDown();

   void OnUpButtonUp();
   void OnDownButtonUp();
   void OnLeftButtonUp();
   void OnRightButtonUp();

   void TurnLeft();
   void TurnRight();
   void MoveForward();
   void MoveBackward();

   bool EntersGravityFieldOf(Planet* planet);
   void TransitionTo(Planet* planet);

   void Jump();
   void ReleaseJump();

   void set_large_planet_observer(PlayerObserver* observer) {
      large_planet_mover_.set_observer(observer);
   }

   bool Update();
   bool is_jumping() const { return small_planet_mover_.is_jumping(); }
   glm::vec3 position() const {
      return game_play_type_ == GAME_PLAY_SMALL ?
             small_planet_mover_.position() :
             large_planet_mover_.position();
   }
   glm::vec3 up() const { return large_planet_mover_.up(); }
   glm::vec3 facing() const { return large_planet_mover_.forward(); }

   glm::mat4 local_rotation() const {
      return large_planet_mover_.local_rotation();
   }

  private:
   bool is_attached_to(Planet* planet) const {
      return small_planet_mover_.is_attached_to(planet) ||
             large_planet_mover_.is_attached_to(planet);
   }

   void UpdateTransition();
   void UpdateMeshPosition();

   SmallPlanetMover small_planet_mover_;
   LargePlanetMover large_planet_mover_;
   GamePlayType game_play_type_;

   glm::vec3 position_;
   glm::vec3 velocity_;
   int transition_frames_;
};

#endif
