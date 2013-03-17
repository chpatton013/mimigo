#include "assets.h"

inline
float radians(float degrees) {
   return degrees * M_PI / 180.0f;
}

Assets::Assets(const std::string&  name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle, Planet *planet):
   translate(translate),
   scale(scale),
   rotate(rotate),
   theta_(5.0),
   planet(planet),
   rotateAngle(rotateAngle),
   up(0)
   {
      Initialize(name, id);
      flag = flag2 = true;
   }

void Assets::Initialize(const std::string& name, const std::string& id){
   mesh = new SceneNode("a" + id);
  // set_bounding_region(new SphericalBoundingRegion(planet->center() + translate, mesh->GetAverageRadius() * 0.25f));
   mesh->set_transformation(glm::translate(planet->center() + translate));
   mesh->apply_transformation(glm::scale(scale));
   mesh->apply_transformation(glm::rotate(rotateAngle, rotate));
   RootNode::Instance()->AddChild(mesh);
 
   mesh->AddChild(SceneNode::Get(name + id));
}

bool Assets::BackAndForth(int begin, int end, float speed) {     
      if(theta_ == end){
         flag = false;
      }
      if(theta_ == begin){
         flag = true;
      }

      if(flag){
         theta_ += speed;
      }
      else{
         theta_ -= speed;
      }

      position_ = planet->center() +
         glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+0.2f);

   UpdateMeshPosition();
   //bounding_region_->set_center(position_);

   return true;
}

bool Assets::UpAndDown(float max, float min, float speedup, float speedDown) {
      theta_ = 80;
           
      if(up > max){
         flag2 = false;
      }
      if(up < min){
         flag2 = true;
      }

      if(flag2){
         up += speedup;
      }
      else{
         up -= speedDown;
      }


      position_ = planet->center() +
         glm::vec3(std::cos(radians(theta_)), std::sin(radians(theta_)), 0.0f) * (planet->radius()+up);

   UpdateMeshPosition();
   //bounding_region_->set_center(position());

   return true;
}

bool Assets::Bounce() {
           
      if(up > .5){
         flag2 = false;
      }
      if(up < 0.0){
         flag2 = true;
      }

      if(flag2){
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
   //bounding_region_->set_center(position());

   return true;
}

void Assets::UpdateMeshPosition() {
   mesh->set_transformation(glm::translate(position_));
   mesh->apply_transformation(glm::scale(0.35f, 0.35f, 0.35f));
}


