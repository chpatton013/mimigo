#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"

namespace {

const float kCameraDistance = 0.5f;

float radians(float degrees) {
   return degrees/180.0*acos(-1.0);
}

}

void Camera::TransitionToLargePlanetMode() {
   large_planet_mode_ = true;
}

void Camera::DebugPrint() {
   std::cout << "camera pos" << std::endl;
   glm_util::Print(camera_pos_);
   std::cout << "camera focus" << std::endl;
   glm_util::Print(camera_focus_);
   std::cout << "camera up" << std::endl;
   glm_util::Print(camera_up_);
}

void Camera::Update() {
   angle_ += rotate_*1.8;
   if (large_planet_mode_) {
      UpdateCamera();
      pos_mover_.Update(camera_pos_);
      focus_mover_.Update(camera_focus_);
      up_mover_.Update(camera_up_);
   }
}

void Camera::UpdateCamera() {
   pos_mover_.Move(camera_pos_, camera_focus_ +
      glm::vec3(std::cos(radians(angle_)),
                0.2f,
                std::sin(radians(angle_)))*kCameraDistance,
      0.9f);
}

void Camera::SetView() {
   glm::mat4 camera = glm::lookAt(
         glm::vec3(camera_pos_),
         glm::vec3(camera_focus_),
         camera_up_);
   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}
