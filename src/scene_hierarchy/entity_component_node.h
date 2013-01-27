#ifndef _ENTITY_COMPONENT_NODE_H_
#define _ENTITY_COMPONENT_NODE_H_

#include "core/entity_component.h"

class EntityComponentNode : public SceneNode {
  public:
   EntityComponentNode(const std::string& id, EntityComponent* entity) :
      SceneNode(id),
      entity_(entity)
   {}

   virtual void AddChild(SceneNode*) { assert(false); }
   virtual void RemoveChild(SceneNode*) { assert(false); }
   virtual void set_children(const std::set<SceneNode*>&)
    { assert(false); }

   virtual void Draw(MatrixStack* matrix_stack) {
      matrix_stack->push();
      matrix_stack->multiply(transform());
      entity_->Draw(matrix_stack);
      matrix_stack->pop();
   }

  private:
   EntityComponent* entity_;
};


#endif
