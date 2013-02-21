#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"

namespace {
float radians(float degrees) { return degrees/180.0*acos(-1.0); }
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
         camera_up_);
   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}
