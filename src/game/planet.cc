#include <glm/glm.hpp>
#include "planet.h"
#include "util/glm_util.h"

bool Planet::PositionWithinGravityField(const glm::vec3& position) {
   return glm_util::magnitude(position - center_) < gravity_radius_;
}

void Planet::Initialize(const std::string& id) {
   mesh = new SceneNode(id);
   mesh->set_transformation(glm::translate(center_));
   mesh->apply_transformation(glm::scale(2.0f*radius_, 2.0f*radius_, 2.0f*radius_));
   RootNode::Instance()->AddChild(mesh);
   mesh->AddChild(SceneNode::Get("planet" + id));
}

void Planet::sideways(float dist){
   float acc = 0.1f;
   /*if(center_.x > move_center.x - (dist / 2) && center_.x < move_center.x + (dist / 2)){
      acc = .2;
   }
   */
   
   if(center_.x > move_center.x + dist){
      turn = false;
   }
  if(center_.x < move_center.x - dist){
      turn = true;
   }  
   if(!turn){
	 acc *= -1.0f;
   }
   center_.x += acc; 
   mesh->set_transformation(glm::translate(center_));
   mesh->apply_transformation(glm::scale(2.0f*radius_, 2.0f*radius_, 2.0f*radius_));

}

void Planet::Pogo(float dist){
   float acc = 0.1f;
   /*
   if(center_.x > move_center.x - (dist / 2) && center_.x < move_center.x + (dist / 2)){
      acc = .2;
   }
   */
   
   if(center_.y > move_center.y + dist){
      turn = false;
   }
   if(center_.y < move_center.y - dist){
      turn = true;
   }
   if(!turn){
     acc *= -1.0f;
   }
    center_.y += acc; 

  mesh->set_transformation(glm::translate(center_));
   mesh->apply_transformation(glm::scale(2.0f*radius_, 2.0f*radius_, 2.0f*radius_));
}
