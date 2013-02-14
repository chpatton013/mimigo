#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include <assert.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <string>
#include "../util/matrix_stack.h"
#include "../util/stl_util.h"

class SceneNode {
  public:
   SceneNode(const std::string& id) :
      visible_(true),
      parent_(NULL),
      id_(id)
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

   // GLMesh integration
   virtual void GetExtents(glm::vec4* min, glm::vec4* max);
   virtual void GetExtentAverages(glm::vec4& min, glm::vec4& max, glm::vec3* avg);
   virtual void GetExtentAverages(glm::vec3* avg);
   virtual float GetCircumscribingRadius();
   virtual float GetInscribingRadius();
   virtual float GetWeightedAverageRadius();
   virtual float GetAverageRadius();

   // statics
   static bool Contains(const std::string& id) {
      return stl_util::ContainsKey(node_map_, id);
   }
   static SceneNode* Get(const std::string& id) {
      assert(stl_util::ContainsKey(node_map_, id));
      return node_map_[id];
   }

  protected:
   glm::mat4 transform_;
   bool visible_;
   SceneNode* parent_;
   std::set<SceneNode*> children_;
   const std::string id_;

   static std::map<std::string, SceneNode*> node_map_;
};

#endif
