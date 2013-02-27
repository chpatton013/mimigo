#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include <string>
#include "core/rotation.h"
#include "core/mover.h"
#include "../gl/gl_mesh.h"

class EntityComposite;
class MatrixStack;

class EntityComponent {
  public:
   EntityComponent() {}
   EntityComponent(const glm::vec3 t, const Rotation& r,
      const glm::vec3& s, const std::string& name);
   virtual ~EntityComponent() {}

   virtual void Draw(MatrixStack* transform);
   virtual bool Update();

   virtual void set_texture(const std::string& texture) {
      std::cout << "set_texture(" << texture << ") not implemented for EntityComponent" << std::endl;
      assert(false);
   }

   virtual glm::vec3 position() const { return position_; }
   virtual Rotation rotation() const { return rotation_; }
   virtual glm::vec3 scale() const { return scale_; }

   virtual void set_should_draw(bool d) { draw_ = d; }
   void Spin(float seconds);

   std::string name() const { return name_; }
   void set_parent(EntityComposite* p);

   virtual void print(int level) const = 0;

   virtual const std::vector<GLMesh*>& meshes() = 0;

  protected:
   bool draw_;
   glm::vec3 position_;
   Rotation rotation_;
   glm::vec3 scale_;
   std::string name_;
   EntityComposite* parent_;

   Mover mover_;
   Rotater rotater_;
   Mover scaler_;
};

#endif
