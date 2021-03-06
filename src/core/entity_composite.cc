#include "core/entity_composite.h"

void EntityComposite::Draw(MatrixStack* transform) {
   if (!draw_)
      return;

   EntityComponent::Draw(transform);

   for (std::vector<EntityComponent*>::iterator it = entities_.begin();
         it != entities_.end(); ++it) {
      if (*it)
         (*it)->Draw(transform);
   }

   transform->pop();
}

bool EntityComposite::Update() {
   EntityComponent::Update();

   for (std::vector<EntityComponent*>::iterator it = entities_.begin();
        it != entities_.end(); ++it) {
      if (*it)
         (*it)->Update();
   }

   return true;
}

void EntityComposite::print(int level) const {
   for (int i = 0; i < level; i++)
      std::cout << "  ";
   std::cout << "|-" << name() << std::endl;
   for (std::vector<EntityComponent*>::const_iterator it = entities_.begin();
         it != entities_.end(); ++it) {
      (*it)->print(level+1);
   }
}

const std::vector<GLMesh*>& EntityComposite::meshes() {
   meshes_.clear();
   for (std::vector<EntityComponent*>::const_iterator it = entities_.begin();
         it != entities_.end(); ++it) {
      const std::vector<GLMesh*>& curr_meshes = (*it)->meshes();
      meshes_.insert(meshes_.end(), curr_meshes.begin(), curr_meshes.end());
   }
   return meshes_;
}
