#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <istream>
#include <vector>
#include <list>
#include <set>
#include "glm/glm.hpp"
#include "core/timer.h"
#include "core/entity.h"
#include "core/entity_composite.h"
#include "scoped_ptr.h"


struct Frame {
   virtual void parse_frame(std::istream& stream) = 0;
};

struct TranslateFrame : public Frame {
   glm::vec3 translate;
   void parse_frame(std::istream& stream);
};

struct RotateFrame : public Frame {
   Rotation rotate;
   void parse_frame(std::istream& stream);
};

struct ScaleFrame : public Frame {
   glm::vec3 scale;
   void parse_frame(std::istream& stream);
};

struct DisplayFrame : public Frame {
   bool display;
   void parse_frame(std::istream& stream);
};

struct LoadAnimationFrame : public Frame {
   std::string animation;
   void parse_frame(std::istream& stream);
};

class Animation : public Timer::Delegate {
  public:
   Animation(const std::map<int, TranslateFrame>& translate_frames,
             const std::map<int, RotateFrame>& rotate_frames,
             const std::map<int, ScaleFrame>& scale_frames,
             const std::map<int, DisplayFrame>& display_frames,
             const std::map<int, LoadAnimationFrame>& loaded_animation_frames,
             const std::set<int>& key_frames,
             const std::vector<std::string>& children,
             const std::string& name) :
      translate_frames_(translate_frames),
      rotate_frames_(rotate_frames),
      scale_frames_(scale_frames),
      display_frames_(display_frames),
      loaded_animation_frames_(loaded_animation_frames),
      key_frames_(key_frames),
      children_(children),
      name_(name),
      entity_(NULL)
   {
   }

   static Animation* LoadFromFile(const std::string& filename);
   void print() const;
   void OnExpiration(const std::string& event);
   void StartAnimation();
   EntityComposite* entity() { return entity_; }

  private:
   void ApplyFrame(const Frame& frame);
   void SwapEntity(const std::string& e);

   std::map<int, TranslateFrame> translate_frames_;
   std::map<int, RotateFrame> rotate_frames_;
   std::map<int, ScaleFrame> scale_frames_;
   std::map<int, DisplayFrame> display_frames_;
   std::map<int, LoadAnimationFrame> loaded_animation_frames_;
   std::set<int> key_frames_;
   std::vector<std::string> children_;
   std::string name_;

   std::set<int>::iterator current_key_frame_;
   EntityComposite* entity_;
};

#endif
