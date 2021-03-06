#include "assets.h"
#include "planet.h"
#include "../spatial_hierarchy/spherical_bounding_region.h"

inline
float radians(float degrees) {
   return degrees * M_PI / 180.0f;
}

Assets::Assets(const std::string&  name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle, Planet *planet, int move):
   translate(translate),
   planet(planet),
   scale(scale),
   rotate(rotate),
   theta_(5.0),
   up(0),
   rotateVal(rotateAngle),
   move(move),
   rotateAngle(rotateAngle)
   {
      Initialize(name, id);
      flag = true;
      glm::vec3 start = glm::vec3(planet->center() + glm::vec3(planet->radius(), 0, 0));
      glm::vec3 end = glm::vec3(planet->center() + translate);
      angle = atan2(end.y - start.y, end.x - start.x);
      angle = angle * (180.0f / M_PI);
   }

void Assets::Initialize(const std::string& name, const std::string& id){
   mesh = new SceneNode("a" + id);
   
   mesh->set_transformation(glm::translate(planet->center() + translate));
   mesh->apply_transformation(glm::scale(scale));
   mesh->apply_transformation(glm::rotate(rotateAngle, rotate));
   RootNode::Instance()->AddChild(mesh);
 
   mesh->AddChild(SceneNode::Get(name + id));
   
   set_bounding_region(new SphericalBoundingRegion(position(), mesh->GetAverageRadius() * .25f));
   printf("radius %f", mesh->GetAverageRadius() );
}

glm::vec3 Assets::position() {
   return planet->center() + glm::vec3(
      glm::cos(radians(theta_)),
      glm::sin(radians(theta_)),
      0.0f
   ) * planet->radius();
}

bool Assets::Update() {
   switch(move) {
      case 0:
         BackAndForth(45.0, 1.0, 1);
         break;
      case 5:
         BackAndForth(100.0, 1.0, 0);
         break;
      case 6:
         CCW(359.0);
         break;
      case 7:
         CW(359.0);
         break;
      case 1:
	UpAndDown(.5, true, .05, .02);
         break;
      case 2:
	UpAndDown(.5, true, .1, .06);
         break;
      case 4:
	UpAndDown(.5, true, .02, .03);
         break;
      case 3:
	 UpAndDown(.5, false, .02, .05);
         break;

   }
   
   
   return true;
}

void Assets::CCW(float speed) { 
    theta_ += speed;
      position_ = planet->center() + glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+0.2f);

   UpdateMeshPosition();
   bounding_region_->set_center(position_);
}

void Assets::CW(float speed) { 
    theta_ += speed;
      position_ = planet->center() + glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+0.2f);

   UpdateMeshPosition();
   bounding_region_->set_center(position_);
}


void Assets::BackAndForth(float dist, float speed, int row) { 
      if(theta_ <= -dist + angle){
         flag = true;
      }
      if(theta_ >= dist + angle){
         flag = false;
      }
      
      if(flag){
         theta_ += speed;
         rotateVal -= 20;
         if(row == 1){
            rotateVal = theta_ * .1;
         }
      }
      else{
         theta_ -= speed;
         rotateVal += 20;
         if(row == 1){
            rotateVal = theta_ * .1;
         }
      }

      position_ = planet->center() + glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+0.2f);

   UpdateMeshPosition();
   bounding_region_->set_center(position_);
}

void Assets::UpAndDown(float dist, bool upward, float speedup, float speedDown) {
      theta_ = 80;
      
      if(upward){ 
         if(up > dist) {
            flag = false;
         }
         else if(up <= 0){
            flag = true;
         }
      }
      else {
         if(up < -dist){
            flag = true;
         }
         else if(up >= 0){
            flag = false;
         }
      }
      
      if(flag){
         up += speedup;
      }
      else{
         up -= speedDown;
      }

      position_ = planet->center() + translate + 
      glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (up);

   UpdateMeshPosition();
   bounding_region_->set_center(position());
}

bool Assets::Bounce() {
           
      if(up > .5){
         flag = false;
      }
      if(up < 0.0){
         flag = true;
      }

      if(flag){
         up += .1f;
         theta_ += 5.0f;

      }
      else{
         up -= .05f;
         theta_ += 5.0f;
      }


      position_ = planet->center() +
         glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+up);


   UpdateMeshPosition();
   bounding_region_->set_center(position());

   return true;
}

void Assets::UpdateMeshPosition() {
   mesh->set_transformation(glm::translate(position_));
   mesh->apply_transformation(glm::scale(scale));
   mesh->apply_transformation(glm::rotate(glm::mat4(), rotateVal, glm::vec3(0.0f, 0.0f, 1.0f)));
}


