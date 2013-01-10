#include "core/entity_component.h"

#include "glm/glm.hpp"

void EntityComponent::Draw(RenderingHelper* transform) {
   if (!draw_)
      return;

   transform->pushMatrix();

   mat4 model_trans;
   model_trans = glm::translate(model_trans, position_);
   model_trans = glm::rotate(model_trans, rotation_.angle, rotation_.axis);
   model_trans = glm::scale(model_trans, scale_);
   transform->multMatrix(model_trans);
}

void EntityComponent::Update() {
   mover_.Update(position_);
   rotater_.Update(rotation_.angle);
   scaler_.Update(scale_);
}

void EntityComponent::set_position(const glm::vec3& p, float seconds) {
   assert(seconds >= 0.0f);
   if (stl_util::Equal(seconds, 0.0f))
      position_ = p;
   else
      mover_.Move(position_, p, seconds);
}

void EntityComponent::set_rotation(const Rotation& r, float seconds) {
   assert(seconds >= 0.0f);
   rotation_.axis = r.axis;
   if (stl_util::Equal(seconds, 0.0f))
      rotation_.angle = r.angle;
   else
      rotater_.Move(rotation_.angle, r.angle - rotation_.angle, seconds);
}

void EntityComponent::set_scale(const glm::vec3& s, float seconds) {
   assert(seconds >= 0.0f);
   if (stl_util::Equal(seconds, 0.0f))
      scale_ = s;
   else
      scaler_.Move(scale_, s, seconds);
}

void EntityComponent::Spin(float seconds) {
   rotation_.axis = Y_AXIS;
   rotater_.Spin(rotation_.angle, 15.0f, seconds);
}
