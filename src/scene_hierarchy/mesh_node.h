#ifndef _MESH_NODE_H_
#define _MESH_NODE_H_

#include "scene_node.h"
#include "gl/gl_mesh.h"

class GLMesh;

class MeshNode : public SceneNode {
  public:
   MeshNode(const std::string& id, GLMesh* mesh) :
      SceneNode(id),
      mesh_(mesh)
   {}

   virtual void AddChild(SceneNode*) { assert(false); }
   virtual void RemoveChild(SceneNode*) { assert(false); }
   virtual void set_children(const std::set<SceneNode*>&)
    { assert(false); }

   virtual void Draw(MatrixStack* matrix_stack) {
      matrix_stack->multiply(transform());
      mesh_->Draw(matrix_stack);
   }

  private:
   GLMesh* mesh_;
};

#endif
