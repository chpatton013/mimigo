#ifndef _ROOT_NODE_H_
#define _ROOT_NODE_H_

#include <set>
#include <utility>

#include "scene_node.h"
#include "collision_node.h"

class RootNode : public SceneNode {
  public:
   static RootNode* Instance() {
      if (!root_)
         root_ = new RootNode();
      return root_;
   }

   virtual void Draw();
   virtual void Draw(MatrixStack*) { assert(0); }

   virtual void AddChild(SceneNode* child, bool collision = false);

   virtual void RemoveChild(SceneNode* child);
   virtual void RemoveChild(const std::string& id)
    { this->RemoveChild(SceneNode::Get(id)); }

   virtual void CalculateCollisions();
   virtual const std::set<std::pair<CollisionNode*, CollisionNode*> >&
    GetCollisions() { return collisions_; }

   virtual void set_visible(bool) { assert(false); }
   virtual bool visible() { assert(false); }

   virtual void PrintTree() { SceneNode::PrintTree(0); }

  private:
   static RootNode* root_;
   RootNode(std::string id="root") :
      SceneNode(id)
   {}
   ~RootNode() {}

   std::set<std::pair<CollisionNode*, CollisionNode*> > collisions_;
};

#endif
