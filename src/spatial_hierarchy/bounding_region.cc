#include "bounding_region.h"
#include "../scene_hierarchy/root_node.h"

BoundingRegion::BoundingRegion() {}
BoundingRegion::~BoundingRegion() {}

void BoundingRegion::create_component(
   const glm::vec3& t,
   const Rotation& r,
   const glm::vec3& s,
   GLMesh* mesh
) {
   brc_ = new BoundingRegionComponent(t, r, s, name_);
   brc_->add_mesh(mesh);
   RootNode::Instance()->AddChild(new EntityComponentNode(name_, brc_));
   SceneNode::Get(name_)->set_visible(true);
}

void BoundingRegion::delete_component() {
   RootNode::Instance()->RemoveChild(name_);
}
