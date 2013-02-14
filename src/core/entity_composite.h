#ifndef ENTITY_COMPOSITE_H_
#define ENTITY_COMPOSITE_H_

#include <assert.h>
#include "core/entity_component.h"
#include "core/entity.h"
#include "global/stl_util.h"

// Composite pattern, cool!
class EntityComposite : public EntityComponent {
  public:
   EntityComposite() {}
   EntityComposite(const glm::vec3 t, const Rotation& r,
         const glm::vec3& s, const std::string& name) :
      EntityComponent(t, r, s, name)
   {}
   virtual ~EntityComposite() {}

   virtual void Draw(MatrixStack* transform);

   virtual void set_texture(const std::string& texture) {
      std::cout << "set_texture() not implemented for EntityComposite" << std::endl;
      assert(false);
   }

   void Add(EntityComponent* e) {
      assert(e);
      assert(!stl_util::Contains(entities_, e));
      e->set_parent(this);
      entities_.push_back(e);
   }

   void Remove(EntityComponent* e)
    { assert(e); stl_util::Remove(entities_, e); }
   size_t size() const { return entities_.size(); }

   bool Update();
   virtual void print(int level) const;

  private:
   std::vector<EntityComponent*> entities_;
};

#endif
