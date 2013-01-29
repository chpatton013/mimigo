#ifndef LINEAR_VALUE_ANIMATOR_H_
#define LINEAR_VALUE_ANIMATOR_H_

#include "callback.h"
#include <SDL/SDL.h>

class LinearValueAnimator {
  public:
   LinearValueAnimator(float* value, float delta, float seconds, Callback& callback) :
      value_(value),
      delta_(delta),
      seconds_(seconds),
      callback_(callback),
      last_ticks_(SDL_GetTicks()),
      start_ticks_(last_ticks_)
   {
      final_value_ = *value_ + delta_;
   }

   void Update();

  private:
   bool time_expired(unsigned int current_ticks) const;
   float interval(unsigned int current_ticks) const;

   float* value_;
   float delta_;
   float final_value_;
   float seconds_;
   Callback callback_;

   unsigned int last_ticks_;
   unsigned int start_ticks_;
};

#endif
