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
      camera_up_(0.0f, 1.0f, 0.0f),
      camera_pos_(0.0f, 0.0f, 2.5f)
   {
   }

   void SetView();

   virtual void OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                             const glm::vec3& facing);

   glm::vec3 position() const { return camera_pos_; }
   glm::vec3 focus() const { return camera_focus_; }

   virtual void Update();

  protected:
   glm::vec3 camera_up_;
   glm::vec3 camera_pos_;
   glm::vec3 camera_focus_;
   glm::vec3 view_vector_;
   Mover focus_mover_;
   Mover pos_mover_;
   Mover up_mover_;
};

#endif
