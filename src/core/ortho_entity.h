#ifndef ORTHO_ENTITY_H
#define ORTHO_ENTITY_H

#include "core/entity.h"
#include "core/mesh_load.h"

class OrthoEntity {
  public:
   OrthoEntity(const std::string& texture, const glm::vec3& p,
               float angle=0.0f, const glm::vec2& s=glm::vec2()) :
      mesh_(MakeSquare()),
      texture_(texture),
      position_(p.x, p.y, p.z),
      angle_(angle),
      scale_(s.x, s.y, 1.0f),
      should_draw_(true)
   {
   }

   void Draw();

   GLMesh* mesh_;
   std::string texture_;
   glm::vec3 position_;
   float angle_;
   glm::vec3 scale_;
   bool should_draw_;
};

#endif
