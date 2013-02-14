#ifndef ENTITY_H
#define ENTITY_H

#include <assert.h>
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "gl/gl_mesh.h"
#include "core/entity_component.h"
#include "core/rotation.h"
#include "core/mover.h"

/**
 * An entity incorporates a collection of meshes and their texture.
 * It does not contain other entities.
 *
 * It contains the world transformations.
 */
class Entity : public EntityComponent {
  public:
   Entity() {}
   Entity(const std::vector<GLMesh*> meshes, const glm::vec3& t,
         const Rotation& r, const glm::vec3& s,
         const std::string& name) :
      EntityComponent(t, r, s, name),
      meshes_(meshes)
   {}
   virtual ~Entity() {}

   void Draw(MatrixStack* transform);

   virtual void set_should_draw(bool d) { draw_ = d; }

   void set_texture(const std::string& texture) { texture_ = texture; }
   std::string texture() const { return texture_; }

   void move_model(const glm::vec3& relative) {
      for (size_t i = 0; i < meshes_.size(); ++i)
         meshes_[i]->move(relative);
   }
   virtual void print(int level) const;

   virtual const std::vector<GLMesh*>& meshes() { return meshes_; }

  private:
   const std::vector<GLMesh*> meshes_;
   std::string texture_;
};

#endif
