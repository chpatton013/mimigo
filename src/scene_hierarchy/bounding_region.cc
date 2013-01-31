#include "../scene_hierarchy/bounding_region.h"

void BoundingRegion::set_instance(glm::vec3& t, Rotation& r, glm::vec3& s) {
   glm::mat4 tm = glm::translate(glm::mat4(1.0f), t),
             rm = glm::rotate(glm::mat4(1.0f), r.angle, r.axis),
             sm = glm::scale(glm::mat4(1.0f), s);

   instance_ = tm * rm * sm;
}
