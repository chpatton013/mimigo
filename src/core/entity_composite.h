#ifndef ENTITY_COMPOSITE_H_
#define ENTITY_COMPOSITE_H_

#include "core/entity_component.h"
#include "core/entity.h"
#include "global/stl_util.h"

// Composite pattern, cool!
class EntityComposite : public EntityComponent {
  public:
   EntityComposite(const glm::vec3 t, const Rotation& r,
         const glm::vec3& s, const std::string& name) :
      EntityComponent(t, r, s, name)
   {}

   virtual void Draw(RenderingHelper* transform);

   virtual void set_texture(const std::string& texture) {
      std::cout << "set_texture() not implemented for EntityComposite" << std::endl;
      assert(false);
   }

   void Add(EntityComponent* e) { entities_.push_back(e); }

   void Remove(EntityComponent* e)
    { stl_util::Remove(entities_, e); }

   void Update();

  private:
   std::vector<EntityComponent*> entities_;
};

#endif
