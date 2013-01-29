#include "large_planet_camera.h"

LargePlanetCamera::LargePlanetCamera(const glm::vec3& focus, const glm::vec3& position) :
   Camera()
{
   camera_focus_ = focus;
   camera_pos_ = position;
}

void LargePlanetCamera::OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                          const glm::vec3& facing) {
   camera_focus_ = position;
   camera_pos_ = position - facing;
   camera_up_ = up;
}

void LargePlanetCamera::Update() {
}
