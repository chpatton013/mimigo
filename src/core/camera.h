#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //perspective, trans etc
#include <glm/gtc/type_ptr.hpp> //value_ptr
#include "../gl/GLSL_helper.h"
#include "../util/matrix_stack.h"
#include "../util/glm_util.h"
#include "../core/mover.h"

class Camera {
  public:
   Camera() :
      angle_(0.0f),
      rotate_(0.0f),
      camera_up_(0.0f, 1.0f, 0.0f),
      camera_pos_(0.0f, 0.0f, 1.0f)
   {UpdateCamera();}

   void SetView();

   virtual void OnPlayerMove(const glm::vec3& p) {
      focus_mover_.Move(camera_focus_, p, 0.45f);
      UpdateCamera();
   }

   void stop_rotate() { rotate_ = 0.0f; }
   void rotate_left() { rotate_ = 1.0f; }
   void rotate_right() { rotate_ = -1.0f; }

   void Update();

  private:
   void UpdateCamera();

   float rotate_;
   float angle_;

   glm::vec3 camera_up_;
   glm::vec3 camera_pos_;
   glm::vec3 camera_focus_;
   glm::vec3 view_vector_;
   Mover focus_mover_;
   Mover pos_mover_;
};

#endif
