#include <glm/glm.hpp>
#include "planet.h"
#include "util/glm_util.h"

bool Planet::PositionWithinGravityField(const glm::vec3& position) {
   return glm_util::magnitude(position - center_) < gravity_radius_;
}

void Planet::Initialize(const std::string& id) {
   SceneNode* mesh = new SceneNode(id);
   mesh->set_transformation(glm::translate(center_));
   float draw_radius;
   if (is_large_planet())
      draw_radius = radius_*1.98f;
   else
      draw_radius = radius_*1.5f;
   mesh->apply_transformation(glm::scale(draw_radius, draw_radius, draw_radius));
   RootNode::Instance()->AddChild(mesh);
   mesh->AddChild(SceneNode::Get("planet" + id));
}

