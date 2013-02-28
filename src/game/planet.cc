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

//down
void Planet::Pogo(){
  //center_.y -= .005;
   if(center_.y > 7.0 ){
      turn = true;
   }
   if(center_.y < 4.0){
      turn = false;
   }
   if(turn){
   	center_.y -= .1;
   }else{
   	center_.y += .1;
   }
   mesh->set_transformation(glm::translate(center_));
}

//up
void Planet::Gopo(){
  //center_.y -= .005;
   if(center_.y < 7.0){
      turn2 = true;
   }
   if(center_.y > 10.0){
      turn2 = false;
   }
   if(turn2){
   	center_.y += .1;
   }else{
   	center_.y -= .1;
   }
   mesh->set_transformation(glm::translate(center_));
}
