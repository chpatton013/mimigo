#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include <assert.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <string>
#include "../util/matrix_stack.h"
#include "../util/stl_util.h"
#include "bounding_region.h"

class SceneNode {
  public:
   SceneNode(const std::string& id) :
      visible_(true),
      parent_(NULL),
      id_(id),
      bounding_region_(NULL)
   {
      assert(!stl_util::ContainsKey(node_map_, id_));
      node_map_[id_] = this;
   }
   virtual ~SceneNode();

   virtual void Draw(MatrixStack* transform);

   virtual void AddChild(const std::string& id)
    { AddChild(SceneNode::Get(id)); }
   virtual void AddChild(SceneNode* child);

   virtual void RemoveChild(const std::string& id)
    { RemoveChild(SceneNode::Get(id)); }
   virtual void RemoveChild(SceneNode* child);

   virtual void DestroyChild(const std::string& id)
    { DestroyChild(SceneNode::Get(id)); }
   virtual void DestroyChild(SceneNode* child);

   virtual void set_children(const std::set<SceneNode*>& children)
    { children_ = children; }

   virtual void set_visible(bool visible) { visible_ = visible; }
   virtual bool visible() { return visible_; }

   SceneNode* parent() const { return parent_; }
   void set_parent(SceneNode* parent);

   const std::string& id() { return id_; }

   void PrintTree(int level);

   void set_transformation(const glm::mat4& transform)
    { transform_ = transform; }
   void apply_transformation(const glm::mat4& transform)
    { transform_ *= transform; }

   const glm::mat4& transform() const { return transform_; }

   static SceneNode* Get(const std::string& id) {
      assert(stl_util::ContainsKey(node_map_, id));
      return node_map_[id];
   }

   virtual BoundingRegion& GetBoundingRegion();

  protected:
   glm::mat4 transform_;
   bool visible_;
   SceneNode* parent_;
   std::set<SceneNode*> children_;
   const std::string id_;

   BoundingRegion* bounding_region_;

   static std::map<std::string, SceneNode*> node_map_;
};

#endif
