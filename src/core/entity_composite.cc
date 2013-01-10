#include "core/entity_composite.h"

void EntityComposite::Draw(RenderingHelper* transform) {
   if (!draw_)
      return;

   EntityComponent::Draw(transform);

   for (std::vector<EntityComponent*>::iterator it = entities_.begin();
         it != entities_.end(); ++it) {
      (*it)->Draw(transform);
   }

   transform->popMatrix();
}

void EntityComposite::Update() {
   EntityComponent::Update();

   for (std::vector<EntityComponent*>::iterator it = entities_.begin();
        it != entities_.end(); ++it) {
      (*it)->Update();
   }
}
