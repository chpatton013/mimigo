#include "bounding_region_component.h"
#include "../gl/GLSL_helper.h"

BoundingRegionComponent::BoundingRegionComponent() :
   EntityComponent()
{}
BoundingRegionComponent::BoundingRegionComponent(
   const glm::vec3 t, const Rotation& r,
   const glm::vec3& s, const std::string& name
) :
   EntityComponent(t, r, s, name)
{}
BoundingRegionComponent::~BoundingRegionComponent() {}

void BoundingRegionComponent::Draw(MatrixStack* transform) {
   if (!draw_)
      return;

   EntityComponent::Draw(transform);

   safe_glUniform1i(g_handles["uUseTexture"], 0);

   for (std::vector<GLMesh*>::const_iterator itr = meshes_.begin();
        itr != meshes_.end(); ++itr) {
      (*itr)->Draw(transform);
   }

   transform->pop();
}

void BoundingRegionComponent::add_mesh(GLMesh* mesh) {
   meshes_.push_back(mesh);
}

void BoundingRegionComponent::print(int level) const {
   for (int i = 0; i < level; i++)
      std::cout << "  ";
   std::cout << "|-" << name() << std::endl;
}
const std::vector<GLMesh*>& BoundingRegionComponent::meshes() {
   return meshes_;
}
