#include "scene_node.h"
#include "root_node.h"
#include "../util/glm_util.h"

#include <utility>

//static
std::map<std::string, SceneNode*> SceneNode::node_map_;

void SceneNode::Draw(MatrixStack* transform) {
   transform->push();
   transform->multiply(transform_);
   if (visible_) {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         (*it)->Draw(transform);
      }
   }
   transform->pop();
}

void SceneNode::AddChild(SceneNode* child) {
   assert(children_.find(child) == children_.end());

   children_.insert(child);
   child->set_parent(this);

   assert(children_.find(child) != children_.end());
   assert(child->parent() == this);
}

void SceneNode::Update(float move, float trans){
   /*for(std::set<SceneNode*>::iterator it = moving_.begin(); it!= moving_.end(); it++) {
      (*it)->Fly(10);
   }*/
   if(dist <= angle - move){
         flag = true;
      }
      if(dist >= angle + move){
         flag = false;
      }

      if(flag){
         dist += 5;
      }
      else{
         dist -= 5;
      } 
   set_transformation(glm::translate(glm::vec3(trans, 0, 0)));     
   apply_transformation(glm::scale(glm::vec3(0.3)));
      apply_transformation(glm::rotate(glm::mat4(), dist, glm::vec3(0.0f, 0.0f, 1.0f)));
}

void SceneNode::Fly(float move) {
   if(ccenter.y <= center.y - move){
         flag = true;
      }
      if(ccenter.y >= center.y + move){
         flag = false;
      }

      if(flag){
         ccenter.y += .05;
      }
      else{
         ccenter.y -= .05;
      }
  set_transformation(glm::rotate(glm::mat4(), a1 - 90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
  apply_transformation(glm::rotate(glm::mat4(), a2 - 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
  apply_transformation(glm::translate(ccenter));
  apply_transformation(glm::scale(glm::mat4(), glm::vec3(s)));
}

void SceneNode::RemoveChild(SceneNode* child) {
   assert(children_.find(child) != children_.end());

   children_.erase(child);
   RootNode::Instance()->AddChild(child);

   assert(child->parent() == RootNode::Instance());
   assert(children_.find(child) == children_.end());
}

void SceneNode::DestroyChild(SceneNode* child) {
   assert(child != NULL);

   // this is my child
   if (children_.find(child) != children_.end()) {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         child->DestroyChild(*it);
      }

      children_.erase(child);
      delete child;
   } else {
      for (std::set<SceneNode*>::iterator it = children_.begin();
            it != children_.end(); ++it) {
         (*it)->DestroyChild(child);
      }
   }
}

void SceneNode::PrintTree(int level) {
   for (int i = 0; i < level*3; i++)
      std::cout << " ";
   std::cout << "|-" << id() << std::endl;
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it)
      (*it)->PrintTree(level + 1);
}

void SceneNode::set_parent(SceneNode* parent) {
   if (parent_)
      parent_->children_.erase(this);
   parent_ = parent;
}

SceneNode::~SceneNode() {
   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      node_map_.erase((*it)->id());
      delete *it;
   }
}

// GLMesh integration
void SceneNode::GetExtents(glm::vec4* min, glm::vec4* max) {
   glm::vec4 running_min(FLT_MAX), running_max(FLT_MIN);

   for (std::set<SceneNode*>::iterator it = children_.begin();
         it != children_.end(); ++it) {
      glm::vec4 current_min, current_max;
      (*it)->GetExtents(&current_min, &current_max);

      running_min.x = std::min(running_min.x, current_min.x);
      running_min.y = std::min(running_min.y, current_min.y);
      running_min.z = std::min(running_min.z, current_min.z);

      running_max.x = std::max(running_max.x, current_max.x);
      running_max.y = std::max(running_max.y, current_max.y);
      running_max.z = std::max(running_max.z, current_max.z);
   }

   *min = running_min;
   *max = running_max;
}
void SceneNode::GetExtentAverages(glm::vec4& min, glm::vec4& max, glm::vec3* avg) {
   avg->x = (max.x - min.x) * 0.5f;
   avg->y = (max.y - min.y) * 0.5f;
   avg->z = (max.z - min.z) * 0.5f;
}
void SceneNode::GetExtentAverages(glm::vec3* avg) {
   glm::vec4 min, max;
   GetExtents(&min, &max);
   GetExtentAverages(min, max, avg);
}
float SceneNode::GetCircumscribingRadius() {
   glm::vec3 avgs;
   GetExtentAverages(&avgs);

   return std::max(std::max(avgs.x, avgs.y), avgs.z);
}
float SceneNode::GetInscribingRadius() {
   glm::vec3 avgs;
   GetExtentAverages(&avgs);

   return std::min(std::min(avgs.x, avgs.y), avgs.z);
}
float SceneNode::GetWeightedAverageRadius() {
   glm::vec4 min, max;
   glm::vec3 avgs;

   GetExtents(&min, &max);
   GetExtentAverages(min, max, &avgs);

   return glm::dot(avgs, avgs) / (avgs.x + avgs.y + avgs.z);
}
float SceneNode::GetAverageRadius() {
   float max = GetCircumscribingRadius(),
         min = GetInscribingRadius();
   return (max - min) * 0.5f + min;
}
