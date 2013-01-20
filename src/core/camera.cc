#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"

namespace {

const float kCameraDistance = 0.5f;
float radians(float degrees) { return degrees/180.0*acos(-1.0); }

}

void Camera::TransitionToLargePlanetMode() {
   large_planet_mode_ = true;
}

void Camera::OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                          const glm::vec3& facing) {
   camera_focus_ = position;
   camera_up_ = up;
}

void Camera::DebugPrint() {
   std::cout << "camera pos" << std::endl;
   glm_util::Print(camera_pos_);
   std::cout << "camera focus" << std::endl;
   glm_util::Print(camera_focus_);
   std::cout << "camera up" << std::endl;
   glm_util::Print(camera_up_);
}

void Camera::Update(const glm::vec3& position) {
   angle_ += rotate_*1.8;
   if (large_planet_mode_) {
      camera_pos_.y = position.y;
      camera_focus_.y = position.y;
   }
}

void Camera::SetView() {
   glm::mat4 camera = glm::lookAt(
         glm::vec3(camera_pos_),
         glm::vec3(camera_focus_),
         camera_up_);
   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}
