#include "entity_component_node.h"

void EntityComponentNode::Draw(MatrixStack* matrix_stack) {
   matrix_stack->push();
   matrix_stack->multiply(transform());
   if (visible_) {
      entity_->Draw(matrix_stack);
   }
	for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         (*it)->Draw(matrix_stack);
      }
   matrix_stack->pop();
}

void EntityComponentNode::AddChild(SceneNode* child) {
   SceneNode::AddChild(child);
}

void EntityComponentNode::GetExtents(glm::vec4* min, glm::vec4* max) {
   glm::vec4 running_min(FLT_MAX), running_max(FLT_MIN);

   const std::vector<GLMesh*>& mesh_vec = entity_->meshes();
   for (std::vector<GLMesh*>::const_iterator it = mesh_vec.begin();
         it != mesh_vec.end(); ++it) {
      glm::vec4 current_min, current_max;
      (*it)->GetExtents(&current_min, &current_max);

      running_min.x = std::min(running_min.x, current_min.x);
      running_min.y = std::min(running_min.y, current_min.y);
      running_min.z = std::min(running_min.z, current_min.z);

      running_max.x = std::max(running_max.x, current_max.x);
      running_max.y = std::max(running_max.y, current_max.y);
      running_max.z = std::max(running_max.z, current_max.z);
   }

   *min = running_min;
   *max = running_max;
}
