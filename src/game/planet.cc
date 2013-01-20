#include <glm/glm.hpp>
#include "planet.h"
#include "util/glm_util.h"

bool Planet::PositionWithinGravityField(const glm::vec3& position) {
   return glm_util::magnitude(position - center_) < gravity_radius_;
}

void Planet::Initialize(const std::string& id) {
   SceneNode* mesh = new SceneNode(id);
   mesh->set_transformation(glm::translate(center_));
   const float draw_radius = radius_ * 1.51f;
   mesh->apply_transformation(glm::scale(draw_radius, draw_radius, draw_radius));
   RootNode::Instance()->AddChild(mesh);
   mesh->AddChild(SceneNode::Get("planet" + id));
}

