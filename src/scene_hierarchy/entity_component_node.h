#ifndef _ENTITY_COMPONENT_NODE_H_
#define _ENTITY_COMPONENT_NODE_H_

#include "scene_node.h"
#include "core/entity_component.h"

class EntityComponentNode : public SceneNode {
  public:
   EntityComponentNode(const std::string& id, EntityComponent* entity) :
      SceneNode(id),
      entity_(entity)
   {}

   virtual void AddChild(SceneNode* child);
   virtual void RemoveChild(SceneNode*) { assert(false); }
   virtual void set_children(const std::set<SceneNode*>&)
    { assert(false); }

   virtual void Draw(MatrixStack* matrix_stack);

   virtual void GetExtents(glm::vec4* min, glm::vec4* max);

  private:
   EntityComponent* entity_;
};

#endif
