#ifndef _EVENT_LOOP_REGISTRAR_H_
#define _EVENT_LOOP_REGISTRAR_H_

#include "core/event_observer.h"

class EventLoopRegistrar {
  public:
   ~EventLoopRegistrar() {
      UnregisterAll();
   }
   void Register(EventObserver* observer);
   void Unregister(EventObserver* observer);
   void UnregisterAll();

  private:
   std::vector<EventObserver*> registered_;
};

#endif
