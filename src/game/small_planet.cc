#include <glm/glm.hpp>
#include "small_planet.h"
#include "util/glm_util.h"

bool SmallPlanet::PositionWithinGravityField(const glm::vec3& position) {
   return glm_util::magnitude(position - center_) < gravity_radius_;
}
