#include "large_planet_camera.h"
#include "core/linear_value_animator.h"
#include "core/callback.h"

LargePlanetCamera::LargePlanetCamera(const glm::vec3& focus, const glm::vec3& position,
                                     const glm::vec3& destination, const glm::vec3& destination_up,
                                     const glm::vec3& destination_facing) :
   Camera()
{
   camera_focus_ = focus;
   camera_pos_ = position;
   Callback callback;
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.x, -destination_up.x - camera_up_.x, 0.5f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.y, -destination_up.y - camera_up_.y, 0.5f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.z, -destination_up.z - camera_up_.z, 0.5f, callback));

   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.x, destination.x - camera_focus_.x, 0.5f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.y, destination.y - camera_focus_.y, 0.5f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.z, destination.z - camera_focus_.z, 0.5f, callback));

   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.x, destination.x - camera_pos_.x - destination_facing.x, 0.2f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.y, destination.y - camera_pos_.y - destination_facing.y, 0.2f, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.z, destination.z - camera_pos_.z - destination_facing.z, 0.2f, callback));
}

void LargePlanetCamera::OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                          const glm::vec3& facing) {
   //camera_focus_ = position;
   //camera_pos_ = position - facing;
   //camera_up_ = up;
}

void LargePlanetCamera::Update() {
   for (std::vector<LinearValueAnimator*>::iterator it = animators_.begin();
         it != animators_.end(); ++it) {
      (*it)->Update();
   }
}
