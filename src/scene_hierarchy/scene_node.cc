#include "scene_node.h"
#include "root_node.h"
#include "bounding_region.h"
#include "spherical_bounding_region.h"
#include "../util/glm_util.h"

#include <utility>

//static
std::map<std::string, SceneNode*> SceneNode::node_map_;

void SceneNode::Draw(MatrixStack* transform) {
   transform->push();
   transform->multiply(transform_);
   if (visible_) {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         (*it)->Draw(transform);
      }
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
   assert(child != NULL);

   // this is my child
   if (children_.find(child) != children_.end()) {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         child->DestroyChild(*it);
      }

      children_.erase(child);
      delete child;
   } else {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         (*it)->DestroyChild(child);
      }
   }
}

void SceneNode::PrintTree(int level) {
   for (int i = 0; i < level*3; i++)
      std::cout << " ";
   std::cout << "|-" << id() << std::endl;
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it)
      (*it)->PrintTree(level + 1);
}

void SceneNode::set_parent(SceneNode* parent) {
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

   if (bounding_region_ != NULL) {
      delete bounding_region_;
   }
}

BoundingRegion& SceneNode::GetBoundingRegion() {
   if (children_.empty()) {
      return *SphericalBoundingRegion::empty_;
   }

   glm::vec3 min(FLT_MAX), max(FLT_MIN);
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it
   ) {
      const glm::vec3& curr_min = (*it)->GetBoundingRegion().GetMin();
      const glm::vec3& curr_max = (*it)->GetBoundingRegion().GetMax();

      min.x = std::min(min.x, curr_min.x);
      min.y = std::min(min.y, curr_min.y);
      min.z = std::min(min.z, curr_min.z);

      max.x = std::max(max.x, curr_max.x);
      max.y = std::max(max.y, curr_max.y);
      max.z = std::max(max.z, curr_max.z);
   }
   glm::vec3 diff = max - min;
   float radius = std::max(std::max(diff.x, diff.y), diff.z) * 0.5;

   // It is expected that every time this function is called, the scene may have
   // changed. Therefore, a new bounding region must be calculated.
   if (bounding_region_ != NULL) {
      delete bounding_region_;
   }
   bounding_region_ = new SphericalBoundingRegion(glm::vec3(0.0f), radius);

   return *bounding_region_;
}
