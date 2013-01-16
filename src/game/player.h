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

class Player {
  public:
   Player(SmallPlanet* planet) :
      planet_rotater_(planet->center(), planet->radius(), position_),
      transition_planet_(planet)
   {
      mesh_ = new SceneNode("player");
      RootNode::Instance()->AddChild(mesh_);
      mesh_->AddChild(SceneNode::Get("bunny"));
      rotation_.axis = planet_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
      TransitionTo(planet);
   }

   void StartMovingLeftAroundAttachedPlanet();
   void StartMovingRightAroundAttachedPlanet();
   void StopMoving();

   void Jump();

   void attach_planet(SmallPlanet* planet) {
      attached_planet_ = planet;
      planet_rotater_ = PlanetRotater(planet->center(), planet->radius(),
            position_);
   }

   void TransitionTo(SmallPlanet* planet);

   void Update();

   static void RotationEndCallback(void* player);

  private:
   void UpdateMesh();
   void RotateBottomToward(SmallPlanet* planet);
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();
   bool IsTopSideOfPlanet() const;

   SceneNode* mesh_;
   SmallPlanet* attached_planet_;
   SmallPlanet* transition_planet_;
   PlanetRotater planet_rotater_;

   Rotater rotater_;

   glm::vec3 position_;
   Rotation planet_rotation_;
   Rotation rotation_;
};

#endif
