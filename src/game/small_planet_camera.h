#ifndef SMALL_PLANET_CAMERA_H_
#define SMALL_PLANET_CAMERA_H_

#include "core/camera.h"

class LinearValueAnimator;

class SmallPlanetCamera : public Camera {
  public:
   SmallPlanetCamera();
   virtual void OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                             const glm::vec3& facing);
   virtual void OnPlayerSwitchPlanets(Planet* planet);
   virtual void Update();

  private:
   LinearValueAnimator* pos_x_animator_;
   LinearValueAnimator* pos_y_animator_;

};

#endif
