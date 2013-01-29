#include <stdio.h>
#include <algorithm>
#include "linear_value_animator.h"

inline
float seconds(int ticks) {
   return ticks / 1000.0f;
}

bool LinearValueAnimator::time_expired(unsigned int current_ticks) const {
   return seconds(current_ticks - start_ticks_) >= seconds_;
}

float LinearValueAnimator::interval(unsigned int current_ticks) const {
   float ticks = std::min(current_ticks - last_ticks_, current_ticks - start_ticks_);
   return seconds(ticks) / seconds_;
}

void LinearValueAnimator::Update() {
   unsigned int current_ticks = SDL_GetTicks();
   *value_ += delta_ * interval(current_ticks);
   if (time_expired(current_ticks)) {
      *value_ = final_value_;
      callback_.Call();
   }
   last_ticks_ = current_ticks;
}

