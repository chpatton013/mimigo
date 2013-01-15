#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <glm/glm.hpp>
#include "util/stl_util.h"
#include <deque>
#include <vector>

class SceneNode;

class Animator {
  public:
   explicit Animator(SceneNode* node) :
      node_(node),
      is_running_(false)
   {
      registrar_.push_back(this);
   }

   Animator& move_to(const glm::vec3& position, float seconds);
   Animator& move_by(const glm::vec3& translation, float seconds);

   Animator& rotate_by(float degrees, const glm::vec3& axis, float seconds);
   Animator& scale_by(const glm::vec3& scale, float seconds);

   Animator& multiply(const glm::mat4& matrix, float seconds);
   Animator& set_to(const glm::mat4& matrix, float seconds);

   Animator& wait(float seconds);

   Animator& set_visible(bool visible);
   void Start();
   static void UpdateAnimators();

  private:
   ~Animator() {
      stl_util::Remove(registrar_, this);
   }

   struct Frame {
      int duration; // In frames.
      bool is_relative; // whether this is a relative/absolute transformation
      glm::mat4 matrix;
   };

   Animator& enqueue_frame(const glm::mat4& matrix, bool is_relative,
                           float seconds);
   int seconds_to_frames(float seconds);
   bool is_running() const { return is_running_; }

   void Update();
   void StartNextFrame();

   glm::mat4 destination_transform_;
   glm::mat4 delta_transform_;
   SceneNode* node_;
   bool is_running_;
   bool is_done_;
   std::deque<Frame> frame_queue_;

   static std::vector<Animator*> registrar_;
};

#endif
