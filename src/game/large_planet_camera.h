#ifndef LARGE_PLANET_CAMERA_H_
#define LARGE_PLANET_CAMERA_H_

#include "core/camera.h"
#include <vector>

class LinearValueAnimator;

class LargePlanetCamera : public Camera {
  public:
   LargePlanetCamera(const glm::vec3& focus, const glm::vec3& position,
                     const glm::vec3& destination, const glm::vec3& destination_up,
                     const glm::vec3& destination_facing);
   virtual void OnPlayerMove(const glm::vec3& position, const glm::vec3& up,
                             const glm::vec3& facing);
   virtual void OnPlayerSwitchPlanets(Planet* planet) {}
   virtual void Update();

  private:
   std::vector<LinearValueAnimator*> animators_;
};

#endif

