#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include <string>
#include "core/rotation.h"
#include "core/mover.h"
#include "scene_hierarchy/bounding_region.h"

class EntityComposite;
class MatrixStack;

class EntityComponent {
  public:
   EntityComponent(const glm::vec3 t, const Rotation& r,
      const glm::vec3& s, const std::string& name);
   EntityComponent(const glm::vec3 t, const Rotation& r,
      const glm::vec3& s, const std::string& name, BoundingRegion* br);

   virtual void Draw(MatrixStack* transform);
   virtual void Update();

   virtual glm::vec3 position() const { return position_; }
   virtual Rotation rotation() const { return rotation_; }
   virtual glm::vec3 scale() const { return scale_; }

   virtual void set_should_draw(bool d) { draw_ = d; }
   void Spin(float seconds);

   std::string name() const { return name_; }
   void set_parent(EntityComposite* p);

   virtual void print(int level) const = 0;

   BoundingRegion& bounding_region() { return *bounding_region_; }

  protected:
   bool draw_;
   glm::vec3 position_;
   Rotation rotation_;
   glm::vec3 scale_;
   std::string name_;
   EntityComposite* parent_;
   BoundingRegion* bounding_region_;

   Mover mover_;
   Rotater rotater_;
   Mover scaler_;
};

#endif
