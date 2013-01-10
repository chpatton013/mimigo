#include "core/ortho_entity.h"
#include "core/gl_mesh.h"
#include "global/stl_util.h"

void OrthoEntity::Draw() {
   if (!should_draw_)
      return;
   mat4 model_trans;
   model_trans = glm::translate(model_trans, position_);
   model_trans = glm::rotate(model_trans, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
   model_trans = glm::scale(model_trans, scale_);
   RenderingHelper helper;
   helper.useModelViewMatrix();
   helper.loadIdentity();
   helper.multMatrix(model_trans);

   mesh_->Draw(&helper);
}
