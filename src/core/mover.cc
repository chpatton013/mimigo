#include "core/mover.h"

inline float* set_value(float* r, float v) {
   if (r)
      *r = v;
   else
      r = new float(v);
   return r;
}

inline void unset_value(float** r) { delete *r; *r = NULL; }

void Rotater::Spin(float& current_rotation, float rotate_speed,
                   float seconds) {
   rotate_speed_ = rotate_speed;
   final_rotation_ =
      set_value(final_rotation_, current_rotation + seconds*rotate_speed*60.0f);
}

void Rotater::Update(float& rotation) {
   if (final_rotation_) {
      if (std::abs(rotation - *final_rotation_) > std::abs(rotate_speed_) &&
          !stl_util::Equal(rotate_speed_, 0.0f)) {
         rotation += rotate_speed_;
      } else {
         rotation = *final_rotation_;
         unset_value(&final_rotation_);
         assert(!final_rotation_);
         rotate_speed_ = 0.0f;
      }
   }
}

void Rotater::Move(float& current_rotate, float rotate_amount, float seconds) {
   rotate_speed_ = rotate_amount / seconds / 60.0f;
   if (stl_util::Equal(rotate_speed_, 0.0f))
      current_rotate += rotate_amount;
   else
      final_rotation_ =
         set_value(final_rotation_, current_rotate + rotate_amount);
}

void Mover::Update(glm::vec3& position) {
   if (move_to_) {
      if (glm_util::magnitude(position - *move_to_) <= move_speed_) {
         position = *move_to_;
         delete move_to_;
         move_to_ = NULL;
      }
      else {
         position += glm::normalize(*move_to_ - position) * move_speed_;
      }
   }
}

void Mover::Move(const glm::vec3& pos, const glm::vec3& where, float seconds) {
   if (move_to_)
      *move_to_ = where;
   else
      move_to_ = new glm::vec3(where);
   move_speed_ = glm_util::magnitude(where - pos) / seconds / 60.0f;
}
