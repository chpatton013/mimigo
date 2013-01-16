#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include <iostream>

#include "../global/stl_util.h"
#include <glm/glm.hpp>

typedef glm::vec2 Point;

namespace {
#define BUTTON_EVENT0(x) virtual void x() {\
   for (size_t i = 0; i < observers_.size(); ++i)\
      observers_[i]->x();\
   }

#define BUTTON_EVENT1(x, type) virtual void x(type param) {\
   for (size_t i = 0; i < observers_.size(); ++i)\
      observers_[i]->x(param);\
   }
}

class EventObserver {
  public:
   virtual void OnMenuButtonDown() {}
   virtual void OnMenuButtonUp() {}
   virtual void OnAltMenuButtonDown() {}
   virtual void OnAltMenuButtonUp() {}

   virtual void OnLoadButtonDown() {}
   virtual void OnLoadButtonUp() {}
   virtual void OnLeftButtonDown() {}
   virtual void OnLeftButtonUp() {}
   virtual void OnRightButtonDown() {}
   virtual void OnRightButtonUp() {}
   virtual void OnUpButtonDown() {}
   virtual void OnUpButtonUp() {}
   virtual void OnDownButtonDown() {}
   virtual void OnDownButtonUp() {}
   virtual void OnHoldButtonDown() {}
   virtual void OnHoldButtonUp() {}
   virtual void OnCameraLeftDown() {}
   virtual void OnCameraLeftUp() {}
   virtual void OnCameraUpDown() {}
   virtual void OnCameraUpUp() {}

   virtual void OnJumpButtonDown() {}
   virtual void OnJumpButtonUp() {}

   virtual void OnLButtonDown(const Point&) {}
   virtual void OnMouseMove(const Point&) {}
};

class EventSubject {
  public:
   void Attach(EventObserver* observer) {
      observers_.push_back(observer);
   }

   void Detach(EventObserver* observer) {
      stl_util::Remove(observers_, observer);
   }

   void DetachAll() { observers_.clear(); }

   BUTTON_EVENT0(OnMenuButtonDown);
   BUTTON_EVENT0(OnMenuButtonUp);
   BUTTON_EVENT0(OnAltMenuButtonDown);
   BUTTON_EVENT0(OnAltMenuButtonUp);

   BUTTON_EVENT0(OnLoadButtonDown);
   BUTTON_EVENT0(OnLoadButtonUp);

   BUTTON_EVENT0(OnLeftButtonDown);
   BUTTON_EVENT0(OnLeftButtonUp);
   BUTTON_EVENT0(OnRightButtonDown);
   BUTTON_EVENT0(OnRightButtonUp);
   BUTTON_EVENT0(OnUpButtonDown);
   BUTTON_EVENT0(OnUpButtonUp);
   BUTTON_EVENT0(OnDownButtonDown);
   BUTTON_EVENT0(OnDownButtonUp);

   BUTTON_EVENT0(OnHoldButtonDown);
   BUTTON_EVENT0(OnHoldButtonUp);
   BUTTON_EVENT0(OnJumpButtonDown);
   BUTTON_EVENT0(OnJumpButtonUp);

   BUTTON_EVENT0(OnCameraLeftDown);
   BUTTON_EVENT0(OnCameraLeftUp);
   BUTTON_EVENT0(OnCameraUpDown);
   BUTTON_EVENT0(OnCameraUpUp);

   BUTTON_EVENT1(OnLButtonDown, const Point&);
   BUTTON_EVENT1(OnMouseMove, const Point&);

  private:
   std::vector<EventObserver*> observers_;
};

#endif
