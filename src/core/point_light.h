#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "core/light.h"

class PointLight : public Light {
  public:
   virtual int type() { return kPointLight; }
};

#endif
