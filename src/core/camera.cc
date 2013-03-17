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
   glm::vec3 pos = position();
   glm::vec3 foc = focus();
   float c_pos[3] = { pos.x, pos.y, pos.z };
   float c_for[3] = { foc.x - pos.x, foc.y - pos.y, foc.z - pos.z };
   safe_glUniform4fv(g_handles["uCameraPosition"], 3, c_pos);
   safe_glUniform4fv(g_handles["uCameraForward"], 3, c_for);
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
}
