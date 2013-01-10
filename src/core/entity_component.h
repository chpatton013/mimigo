#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H

#include <string>
#include "core/rotation.h"
#include "core/mover.h"
#include "core/MStackHelp.h"

class EntityComponent {
  public:
   EntityComponent(const glm::vec3 t, const Rotation& r,
         const glm::vec3& s, const std::string& name) :
      draw_(true),
      position_(t),
      rotation_(r),
      scale_(s),
      name_(name)
   {}
   virtual void Draw(RenderingHelper* transform);
   virtual void Update();

   virtual void set_position(const glm::vec3& p, float seconds=0.0f);
   virtual void set_rotation(const Rotation& r, float seconds=0.0f);
   virtual void set_scale(const glm::vec3& s, float seconds=0.0f);
   virtual void set_texture(const std::string& texture) = 0;

   virtual glm::vec3 position() const { return position_; }
   virtual Rotation rotation() const { return rotation_; }
   virtual glm::vec3 scale() const { return scale_; }

   virtual void set_should_draw(bool d) { draw_ = d; }
   void Spin(float seconds);

   std::string name() const { return name_; }

  protected:
   bool draw_;
   glm::vec3 position_;
   Rotation rotation_;
   glm::vec3 scale_;
   std::string name_;

   Mover mover_;
   Rotater rotater_;
   Mover scaler_;
};

#endif
