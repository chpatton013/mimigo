#include "assets.h"

Assets::Assets(const std::string&  name, const std::string& id, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float rotateAngle):
   translate(translate),
   scale(scale),
   rotate(rotate),
   rotateAngle(rotateAngle)
   {
      Initialize(name, id);
   }

void Assets::Initialize(const std::string& name, const std::string& id){
   SceneNode *mesh = new SceneNode("a" + id);
   mesh->set_transformation(glm::translate(translate));
   mesh->apply_transformation(glm::scale(scale));
  mesh->apply_transformation(glm::rotate(rotateAngle, rotate));
   RootNode::Instance()->AddChild(mesh);

   mesh->AddChild(SceneNode::Get(name + id));
}
