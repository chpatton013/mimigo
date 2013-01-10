#ifndef _TIMER_H_
#define _TIMER_H_

#include <string>

class Timer {
  public:
   class Delegate {
     public:
      virtual void OnExpiration(const std::string& event_name) = 0;
   };

   Timer(Delegate* delegate, const std::string& event_name)
            : delegate_(delegate),
              event_name_(event_name) {}

   void OnExpiration() {
      delegate_->OnExpiration(event_name_);
   }

  private:
   Delegate* delegate_;
   std::string event_name_;
};

#endif
