#include "../core/event_loop.h"
#include "../core/event_loop_registrar.h"
#include "../global/stl_util.h"

void EventLoopRegistrar::Register(EventObserver* observer) {
   EventLoop::Instance()->Attach(observer);
   registered_.push_back(observer);
}

void EventLoopRegistrar::Unregister(EventObserver* observer) {
   EventLoop::Instance()->Detach(observer);
   stl_util::Remove(registered_, observer);
}

void EventLoopRegistrar::UnregisterAll() {
   for (size_t i = 0; i < registered_.size(); ++i)
      EventLoop::Instance()->Detach(registered_[i]);
}
