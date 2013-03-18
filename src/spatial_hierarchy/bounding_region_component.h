#pragma once

#include "../core/entity_component.h"
#include <vector>
#include "../gl/gl_mesh.h"

class BoundingRegionComponent : public EntityComponent {
  public:
   BoundingRegionComponent();
   BoundingRegionComponent(
      const glm::vec3 t, const Rotation& r,
      const glm::vec3& s, const std::string& name
   );
   virtual ~BoundingRegionComponent();

   virtual void Draw(MatrixStack* transform);

   virtual void add_mesh(GLMesh* mesh);

   virtual void print(int level) const;
   virtual const std::vector<GLMesh*>& meshes();

  protected:
   std::vector<GLMesh*> meshes_;
};
