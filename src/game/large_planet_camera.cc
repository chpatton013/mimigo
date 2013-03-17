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
   AnimateToNewCameraState(destination, destination_up, destination_facing, 0.5f);
}

void LargePlanetCamera::OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                          const glm::vec3& facing) {
   AnimateToNewCameraState(position, up, facing, 0.2f);
}

void LargePlanetCamera::AnimateToNewCameraState(const glm::vec3& destination, const glm::vec3& destination_up,
                                                const glm::vec3& destination_facing, float time) {
   for (unsigned int i = 0; i < animators_.size(); ++i)
      delete animators_[i];
   animators_.clear();
   Callback callback;
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.x, destination_up.x - camera_up_.x, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.y, destination_up.y - camera_up_.y, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_up_.z, destination_up.z - camera_up_.z, time, callback));

   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.x, destination.x - camera_focus_.x, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.y, destination.y - camera_focus_.y, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_focus_.z, destination.z - camera_focus_.z, time, callback));

   glm::vec3 up = destination_up / 3.0f;
   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.x, destination.x - camera_pos_.x - destination_facing.x + up.x, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.y, destination.y - camera_pos_.y - destination_facing.y + up.y, time, callback));
   animators_.push_back(new LinearValueAnimator(
            &camera_pos_.z, destination.z - camera_pos_.z - destination_facing.z + up.z, time, callback));
}

void LargePlanetCamera::Update() {
   for (std::vector<LinearValueAnimator*>::iterator it = animators_.begin();
         it != animators_.end(); ++it) {
      (*it)->Update();
   }

   Camera::Update();
}
