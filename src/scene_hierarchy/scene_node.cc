#include "scene_node.h"
#include "root_node.h"
#include "../util/glm_util.h"

//static
std::map<std::string, SceneNode*> SceneNode::node_map_;

void SceneNode::Draw(MatrixStack* transform) {
   transform->push();
   transform->multiply(transform_);
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      (*it)->Draw(transform);
   }
   transform->pop();
}

void SceneNode::AddChild(SceneNode* child) {
   assert(children_.find(child) == children_.end());

   children_.insert(child);
   child->set_parent(this);

   assert(children_.find(child) != children_.end());
   assert(child->parent() == this);
}

void SceneNode::RemoveChild(SceneNode* child) {
   assert(children_.find(child) != children_.end());

   children_.erase(child);
   RootNode::Instance()->AddChild(child);

   assert(child->parent() == RootNode::Instance());
   assert(children_.find(child) == children_.end());
}

void SceneNode::DestroyChild(SceneNode* child) {
   SceneNode::RemoveChild(child);
   RootNode::Instance()->RemoveChild(child);
}

void SceneNode::PrintTree(int level) {
   for (int i = 0; i < level*3; i++)
      std::cout << " ";
   std::cout << "|-" << id() << std::endl;
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it)
      (*it)->PrintTree(level + 1);
}

void  SceneNode::set_parent(SceneNode* parent) {
   if (parent_)
      parent_->children_.erase(this);
   parent_ = parent;
}

SceneNode::~SceneNode() {
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      node_map_.erase((*it)->id());
      delete *it;
   }
}
