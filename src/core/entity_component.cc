#include "core/entity_component.h"
#include "core/entity_composite.h"
#include "global/handles.h"
#include "scene_hierarchy/spherical_bounding_region.h"

#include "glm/glm.hpp"

EntityComponent::EntityComponent(const glm::vec3 t, const Rotation& r,
   const glm::vec3& s, const std::string& name) :
      draw_(true),
      position_(t),
      rotation_(r),
      scale_(s),
      name_(name),
      parent_(NULL)
{
}
EntityComponent::EntityComponent(const glm::vec3 t, const Rotation& r,
   const glm::vec3& s, const std::string& name, BoundingRegion* br) :
      draw_(true),
      position_(t),
      rotation_(r),
      scale_(s),
      name_(name),
      parent_(NULL),
      bounding_region_(br)
{
}

void EntityComponent::set_parent(EntityComposite* p) {
   assert(p);
   if (parent_)
      parent_->Remove(this);
   parent_ = p;
}

void EntityComponent::Draw(MatrixStack* transform) {
   if (!draw_)
      return;

   transform->push();

   glm::mat4 model_trans;
   model_trans = glm::translate(model_trans, position_);
   model_trans = glm::rotate(model_trans, rotation_.angle, rotation_.axis);
   model_trans = glm::scale(model_trans, scale_);
   transform->multiply(model_trans);
}

void EntityComponent::Update() {
   mover_.Update(position_);
   rotater_.Update(rotation_.angle);
   scaler_.Update(scale_);
}

void EntityComponent::Spin(float seconds) {
   rotation_.axis = Y_AXIS;
   rotater_.Spin(rotation_.angle, 15.0f, seconds);
}
