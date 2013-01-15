#include "animator.h"
#include "scene_hierarchy/scene_node.h"
#include <glm/gtx/vector_angle.hpp>
#include "util/glm_util.h"
#ifndef FPS
#define FPS 60
#endif

const bool kRelative = true;
const bool kAbsolute = false;

std::vector<Animator*> Animator::registrar_;

void Animator::UpdateAnimators() {
   std::vector<Animator*> to_delete;
   for (std::vector<Animator*>::iterator it = registrar_.begin();
         it != registrar_.end(); ++it)
      if ((*it)->frame_queue_.empty() && (*it)->is_running())
         to_delete.push_back(*it);
   stl_util::RemoveAllOf(registrar_, to_delete);

   for (std::vector<Animator*>::iterator it = registrar_.begin();
         it != registrar_.end(); ++it)
      (*it)->Update();
}

Animator& Animator::move_to(const glm::vec3& position, float seconds) {
   return enqueue_frame(glm::translate(glm::mat4(1.0f), position),
                        kAbsolute, seconds);
}

Animator& Animator::move_by(const glm::vec3& translation, float seconds) {
   return enqueue_frame(glm::translate(glm::mat4(1.0f), translation),
                        kRelative, seconds);
}

Animator& Animator::rotate_by(float degrees, const glm::vec3& axis,
                              float seconds) {
   return enqueue_frame(glm::rotate(glm::mat4(1.0f), degrees, axis),
                        kRelative, seconds);
}

Animator& Animator::scale_by(const glm::vec3& scale, float seconds) {
   return enqueue_frame(glm::scale(glm::mat4(1.0f), scale), kRelative, seconds);
}

Animator& Animator::multiply(const glm::mat4& matrix, float seconds) {
   return enqueue_frame(matrix, kRelative, seconds);
}

Animator& Animator::set_to(const glm::mat4& matrix, float seconds) {
   return enqueue_frame(matrix, kAbsolute, seconds);
}

Animator& Animator::wait(float seconds) {
   return enqueue_frame(glm::mat4(1.0f), kRelative, seconds);
}

Animator& Animator::set_visible(bool visible) {
   return *this;
}

void Animator::Start() {
   is_running_ = true;
   StartNextFrame();
}

Animator& Animator::enqueue_frame(const glm::mat4& matrix, bool is_relative,
                                  float seconds) {
   assert(!is_running());
   Frame frame;
   frame.matrix = matrix;
   frame.is_relative = is_relative;
   frame.duration = seconds_to_frames(seconds);

   frame_queue_.push_back(frame);
   return *this;
}

int Animator::seconds_to_frames(float seconds) {
   return int(seconds * FPS);
}

void Animator::StartNextFrame() {
   if (frame_queue_.empty())
      return;

   if (frame_queue_.front().is_relative) {
      destination_transform_ = node_->transform() *
                               frame_queue_.front().matrix;
   } else {
      destination_transform_ = frame_queue_.front().matrix;
   }
   delta_transform_ = (destination_transform_ - node_->transform()) /
      frame_queue_.front().duration;
}

void Animator::Update() {
   if (is_running()) {
      node_->apply_transformation(node_->transform() + delta_transform_);
      if (!--frame_queue_.front().duration) {
         frame_queue_.pop_front();
         node_->apply_transformation(destination_transform_);
         StartNextFrame();
      }
   }
}
