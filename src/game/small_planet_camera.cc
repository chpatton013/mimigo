#include "small_planet_camera.h"
#include "core/linear_value_animator.h"

SmallPlanetCamera::SmallPlanetCamera() :
   Camera(),
   pos_x_animator_(NULL),
   pos_y_animator_(NULL)
{
}

void SmallPlanetCamera::OnPlayerSwitchPlanets(Planet* planet) {
   if (pos_x_animator_)
      delete pos_x_animator_;
   if (pos_y_animator_)
      delete pos_y_animator_;
   Callback callback;
   pos_x_animator_ = new LinearValueAnimator(
         &camera_pos_.x, planet->center().x - camera_pos_.x, 0.3f, callback);
   pos_y_animator_ = new LinearValueAnimator(
         &camera_pos_.y, planet->center().y - camera_pos_.y, 0.3f, callback);
}

void SmallPlanetCamera::OnPlayerMove(
      const glm::vec3& position, const glm::vec3& up, const glm::vec3& facing
) {
   camera_focus_ = position;
   assert(true || up.x || facing.x);
}

void SmallPlanetCamera::Update() {
   if (pos_x_animator_)
      pos_x_animator_->Update();
   if (pos_y_animator_)
      pos_y_animator_->Update();
}
