#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/GLSL_helper.h" //perspective, trans etc
#include "core/entity.h"
#include "global/handles.h"
#include "global/glm_util.h"
#include "global/stl_util.h"
#include <limits>

void Entity::Draw(RenderingHelper* transform) {
   if (!draw_)
      return;

   EntityComponent::Draw(transform);

   // Bind texture
   if (stl_util::ContainsKey(g_textures, texture_)) {
      glEnable(GL_TEXTURE_2D);
      glActiveTexture(GL_TEXTURE0);
      safe_glUniform1i(g_handles["uTextureUnit"], 0);
      safe_glUniform1i(g_handles["uUseTexture"], 1);
      glBindTexture(GL_TEXTURE_2D, g_textures[texture_]);
   } else {
      safe_glUniform1i(g_handles["uUseTexture"], 0);
   }

   for (std::vector<GLMesh*>::const_iterator itr = meshes_.begin();
        itr != meshes_.end(); ++itr) {
      (*itr)->Draw(transform);
   }

   transform->popMatrix();
}
