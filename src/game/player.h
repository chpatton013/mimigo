#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "core/mesh_load.h"
#include "gl/gl_mesh.h"
#include "small_planet.h"
#include "planet_rotater.h"
#include "scene_hierarchy/mesh_node.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/scene_node.h"

class Player {
  public:
   Player(SmallPlanet* planet) :
      rotater_(planet->center(), planet->radius())
   {
      mesh_ = new SceneNode("player");
      RootNode::Instance()->AddChild(mesh_);
      mesh_->AddChild(SceneNode::Get("bunny"));
   }

   void StartMovingLeftAroundAttachedPlanet();
   void StartMovingRightAroundAttachedPlanet();
   void StopMoving();

   void Jump();

   void attach_planet(SmallPlanet* planet) {
      attached_planet_ = planet;
      rotater_ = PlanetRotater(planet->center(), planet->radius());
   }

   void Update();

  private:
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();
   bool IsTopSideOfPlanet() const;

   SceneNode* mesh_;
   SmallPlanet* attached_planet_;
   PlanetRotater rotater_;
};

#endif
