#include "../core/camera.h"
#include "../global/handles.h"
#include "../util/stl_util.h"
#include "../core/view_frustum_cull.h"
#include <stdio.h>

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
   glm::mat4 camera = lookAt();
   glm::mat4 comboMatrix = projection * camera;
   ExtractPlanesGL(comboMatrix, false);

   safe_glUniformMatrix4fv(g_handles["uViewMatrix"], glm::value_ptr(camera));
}

glm::mat4 Camera::lookAt() const {
   return glm::lookAt(
      glm::vec3(camera_pos_),
      glm::vec3(camera_focus_),
      camera_up_
   );
}

void print_vec(const glm::vec3& v) {
   printf("[%.2f,%.2f,%.2f]", v.x, v.y, v.z);
}
void Camera::print() {
   printf("pos:");
   print_vec(camera_pos_);
   printf("\n");
   printf("up:");
   print_vec(camera_up_);
   printf("\n");
   printf("focus:");
   print_vec(camera_focus_);
   printf("\n");
}
