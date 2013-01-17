#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "core/mesh_load.h"
#include "core/rotation.h"
#include "gl/gl_mesh.h"
#include "small_planet.h"
#include "planet_rotater.h"
#include "core/mover.h"
#include "scene_hierarchy/mesh_node.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"

class PlayerObserver {
  public:
   virtual void OnPlayerMove(const glm::vec3& where, const glm::vec3& up) = 0;
};

class Player {
  public:
   Player(SmallPlanet* planet) :
      transition_planet_(planet),
      planet_rotater_(planet->center(), planet->radius(), position_),
      is_jumping_(false),
      observer_(NULL)
   {
      mesh_ = new SceneNode("player");
      RootNode::Instance()->AddChild(mesh_);
      mesh_->AddChild(SceneNode::Get("bunny"));
      rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
      left_right_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
      TransitionTo(planet);
   }

   void StartMovingUpAroundAttachedPlanet();
   void StartMovingDownAroundAttachedPlanet();
   void StartMovingLeftAroundAttachedPlanet();
   void StartMovingRightAroundAttachedPlanet();
   void StopMoving();

   bool EntersGravityFieldOf(SmallPlanet* planet);

   void Jump();

   void attach_planet(SmallPlanet* planet) {
      attached_planet_ = planet;
      planet_rotater_ = PlanetRotater(planet->center(), planet->radius(),
            position_);
   }

   void TransitionTo(SmallPlanet* planet);

   void Update();

   static void RotationEndCallback(void* player);

   void register_observer(PlayerObserver* observer) {
      observer_ = observer;
   }

  private:
   void UpdateMesh();
   void RotateBottomToward(SmallPlanet* planet);
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();
   bool IsTopSideOfPlanet();
   bool IsRightSideOfPlanet();

   bool is_jumping() const { return is_jumping_; }

   SceneNode* mesh_;
   SmallPlanet* attached_planet_;
   SmallPlanet* transition_planet_;
   PlanetRotater planet_rotater_;

   Rotater rotater_;

   glm::vec3 position_;
   Rotation rotation_;
   Rotation left_right_rotation_;
   bool is_jumping_;

   PlayerObserver* observer_;
};

#endif
