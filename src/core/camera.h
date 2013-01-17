#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //perspective, trans etc
#include <glm/gtc/type_ptr.hpp> //value_ptr
#include "game/player.h"
#include "gl/GLSL_helper.h"
#include "util/matrix_stack.h"
#include "util/glm_util.h"
#include "core/mover.h"

class Camera : public PlayerObserver {
  public:
   Camera() :
      large_planet_mode_(false),
      angle_(180.0f),
      rotate_(0.0f),
      camera_up_(0.0f, 1.0f, 0.0f),
      camera_pos_(0.0f, 0.0f, 1.0f)
   {UpdateCamera();}

   void SetView();
   void DebugPrint();

   virtual void OnPlayerMove(const glm::vec3& position, const glm::vec3& up) {
      focus_mover_.Move(camera_focus_, position, 0.45f);
      pos_mover_.Move(camera_pos_, position, 0.45f);
      up_mover_.Move(camera_up_, up, 0.45f);
      UpdateCamera();
   }

   void move(const glm::vec3& p) {
      camera_pos_ += p;
      camera_focus_ += p;
      UpdateCamera();
   }

   glm::vec3 position() const { return camera_pos_; }

   void stop_rotate() { rotate_ = 0.0f; }
   void rotate_left() { rotate_ = 1.0f; }
   void rotate_right() { rotate_ = -1.0f; }
   void TransitionToLargePlanetMode();

   void Update();

  private:
   void UpdateCamera();
   bool large_planet_mode_;

   float rotate_;
   float angle_;

   glm::vec3 camera_up_;
   glm::vec3 camera_pos_;
   glm::vec3 camera_focus_;
   glm::vec3 view_vector_;
   Mover focus_mover_;
   Mover pos_mover_;
   Mover up_mover_;
};

#endif
