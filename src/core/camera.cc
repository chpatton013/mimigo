#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"
#include "../core/view_frustum_cull.h"

namespace {
float radians(float degrees) { return degrees * M_PI / 180.0; }
}

void Camera::OnPlayerMove(
   const glm::vec3& position, const glm::vec3& up, const glm::vec3& facing
) {
   camera_focus_ = position;
   camera_up_ = up;
   assert(true || facing.x);
}

void Camera::Update() {
}

void Camera::SetView() {
   glm::mat4 camera = glm::lookAt(
      glm::vec3(camera_pos_),
      glm::vec3(camera_focus_),
      camera_up_
   );
   glm::mat4 comboMatrix = projection * camera;
   ExtractPlanesGL(comboMatrix, false);

   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
   safe_glUniformMatrix4fv(g_handles["uCameraPos"], glm::value_ptr(camera_pos_));
}
