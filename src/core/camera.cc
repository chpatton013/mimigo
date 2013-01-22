#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"

namespace {
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

void Camera::Update(const glm::vec3& position, const glm::mat4& local_axes) {
   if (large_planet_mode_) {
      camera_focus_ = position;
      camera_pos_ = position - glm::vec3(local_axes[0][2], local_axes[1][2], local_axes[2][2]);
      camera_up_ = -glm::vec3(local_axes[0][1], local_axes[1][1], local_axes[2][1]);
   }
}

void Camera::SetView() {
   glm::mat4 camera = glm::lookAt(
         glm::vec3(camera_pos_),
         glm::vec3(camera_focus_),
         camera_up_);
   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}
