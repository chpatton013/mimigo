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
      mesh_(static_cast<MeshNode*>(SceneNode::Get("bunny"))),
      rotater_(planet->center())
   {}

   void StartMovingLeftAroundAttachedPlanet();
   void StartMovingRightAroundAttachedPlanet();
   void StopMoving();

   void attach_planet(SmallPlanet* planet)
    { attached_planet_ = planet; rotater_ = PlanetRotater(planet->center()); }

  private:
   void StartMovingCounterClockwiseAroundAttachedPlanet();
   void StartMovingClockwiseAroundAttachedPlanet();
   bool IsTopSideOfPlanet() const;

   MeshNode* mesh_;
   SmallPlanet* attached_planet_;
   PlanetRotater rotater_;
};

#endif
