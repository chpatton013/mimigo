#ifndef LINEAR_VALUE_ANIMATOR_H_
#define LINEAR_VALUE_ANIMATOR_H_

#include "callback.h"

template <class T>
class LinearValueAnimator {
  public:
   LinearValueAnimator(T* value, T delta, float time, Callback& callback, unsigned int current_ticks) :
      value_(value),
      delta_(delta),
      time_(time),
      callback_(callback),
      last_ticks_(current_ticks),
      start_ticks_(current_ticks)
   {
      final_value_ = *value_ + delta_;
   }

   void Update(unsigned int current_ticks);

  private:
   bool time_expired(unsigned int current_ticks) const;
   float interval(unsigned int current_ticks) const;

   T* value_;
   T delta_;
   T final_value_;
   float time_;
   Callback callback_;

   unsigned int last_ticks_;
   unsigned int start_ticks_;
};

inline
float seconds(int ticks) {
   return ticks / 1000.0f;
}

template <class T>
bool LinearValueAnimator<T>::time_expired(unsigned int current_ticks) const {
   return seconds(current_ticks - start_ticks_) >= time_;
}

template <class T>
float LinearValueAnimator<T>::interval(unsigned int current_ticks) const {
   float ticks = std::min(current_ticks - last_ticks_, current_ticks - start_ticks_);
   return seconds(ticks) / time_;
}

template <class T>
void LinearValueAnimator<T>::Update(unsigned int current_ticks) {
   *value_ += delta_ * interval(current_ticks);
   if (time_expired(current_ticks)) {
      *value_ = final_value_;
      callback_.Call();
   }
   last_ticks_ = current_ticks;
}

#endif
