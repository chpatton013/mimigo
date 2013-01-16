#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"

namespace {

const float kCameraDistance = 3.5f;

float radians(float degrees) {
   return degrees/180.0*acos(-1.0);
}

}
void Camera::Update() {
   angle_ += rotate_*1.8;
   UpdateCamera();
   pos_mover_.Update(camera_pos_);
   focus_mover_.Update(camera_focus_);
}

void Camera::UpdateCamera() {
}

void Camera::SetView() {
   glm::mat4 camera = glm::lookAt(
         glm::vec3(camera_pos_),
         glm::vec3(camera_focus_),
         camera_up_);
   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}
