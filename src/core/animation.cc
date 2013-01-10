#include "core/animation.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include "global/stl_util.h"
#include "global/handles.h"
#include "core/event_loop.h"
#include "core/entity.h"

using namespace std;

void parse_bool(std::istream& stream, bool* truthiness) {
   string word;
   stream >> word;
   if (word == "true")
      *truthiness = true;
   else
      *truthiness = false;
}

void parse_vec3(std::istream& stream, glm::vec3* vec) {
   stream >> vec->x;
   stream >> vec->y;
   stream >> vec->z;
}

void parse_rotation(std::istream& stream, Rotation* rot) {
   stream >> rot->angle;
   parse_vec3(stream, &rot->axis);
}

void TranslateFrame::parse_frame(std::istream& stream) {
   parse_vec3(stream, &translate);
}

void RotateFrame::parse_frame(std::istream& stream) {
   parse_rotation(stream, &rotate);
}

void ScaleFrame::parse_frame(std::istream& stream) {
   parse_vec3(stream, &scale);
}

void DisplayFrame::parse_frame(std::istream& stream) {
   parse_bool(stream, &display);
}

void LoadAnimationFrame::parse_frame(std::istream& stream) {
   stream >> animation;
}

std::istream& operator >>(std::istream& stream, Frame& frame) {
   return stream;
}

void parse_children(istream& stream, vector<string>* strs) {
   string line, command;
   while (getline(stream, line)) {
      istringstream istream(line);
      istream >> command;
      if (command == "end")
         return;
      strs->push_back(command);
   }
}

Animation* Animation::LoadFromFile(const std::string& filename) {
   if (g_animations[filename])
      return g_animations[filename];

   ifstream in(filename.c_str());
   string line;

   map<int, TranslateFrame> translate_frames;
   map<int, RotateFrame> rotate_frames;
   map<int, ScaleFrame> scale_frames;
   map<int, DisplayFrame> display_frames;
   map<int, LoadAnimationFrame> loaded_animation_frames;
   vector<string> children;
   set<int> key_frames;
   int line_num = 0, frame_num;

   istringstream sin(line);
   while (getline(in, line)) {
      istringstream stream(line);
      string command;
      stream >> command;
      if (command == "{") {
         stream >> frame_num;
      } else if (command == "children") {
         parse_children(in, &children);
      } else if (command == "run") {
         loaded_animation_frames[frame_num] = LoadAnimationFrame();
         loaded_animation_frames[frame_num].parse_frame(stream);
         key_frames.insert(frame_num);
      } else if (command == "translate") {
         translate_frames[frame_num] = TranslateFrame();
         translate_frames[frame_num].parse_frame(stream);
         key_frames.insert(frame_num);
      } else if (command == "rotate") {
         rotate_frames[frame_num] = RotateFrame();
         rotate_frames[frame_num].parse_frame(stream);
         key_frames.insert(frame_num);
      } else if (command == "scale") {
         scale_frames[frame_num] = ScaleFrame();
         scale_frames[frame_num].parse_frame(stream);
         key_frames.insert(frame_num);
      } else if (command == "display") {
         display_frames[frame_num] = DisplayFrame();
         display_frames[frame_num].parse_frame(stream);
         key_frames.insert(frame_num);
      } else if (command == "}" || command == "#" || command.empty()) {
      } else {
         cout << "error parsing " << filename << ": bad command: " << command <<
            " on line " << ++line_num << endl;
      }
   }

   return (g_animations[filename] = new Animation(
      translate_frames, rotate_frames, scale_frames, display_frames,
      loaded_animation_frames, key_frames, children, filename));
}

void Animation::print() const {
}

inline float duration(int frame_1, int frame_2) {
   return (frame_2 - frame_1) / 60.0f;
}

void Animation::OnExpiration(const std::string& event_name) {
#ifdef TEST_ANIMATION
   c + s("//////////////////KEYFRAME START");
#endif

   set<int>::iterator next_key_frame = current_key_frame_;
   ++next_key_frame;
   const float duration_until_next_key_frame =
      duration(*current_key_frame_, *next_key_frame);
   if (stl_util::ContainsKey(loaded_animation_frames_, *current_key_frame_)) {
      string a_file = loaded_animation_frames_[*current_key_frame_].animation;
#ifdef TEST_ANIMATION
      c + s("loading animation, %s at frame=%d", a_file.c_str(),
         *current_key_frame_);
      c + s("immediately");
#endif
      LoadFromFile(a_file)->StartAnimation();
   }
   if (stl_util::ContainsKey(display_frames_, *current_key_frame_)) {
#ifdef TEST_ANIMATION
      c + s("setting display, frame=%d", *current_key_frame_);
      c + s("immediately");
#endif
      entity_->set_should_draw(display_frames_[*current_key_frame_].display);
   }

   if (current_key_frame_ == key_frames_.end() ||
       duration_until_next_key_frame < 0.0f) {
#ifdef TEST_ANIMATION
      c + s("//////////////////ANIMATION END");
      //exit(0);
#endif
      return;
   }

#ifdef TEST_ANIMATION
   c + s("next key_frame in %lf seconds", duration_until_next_key_frame);
#endif

   //TODO: this could use a lot of cleaning up.
   bool translate_done =
    !stl_util::ContainsKey(translate_frames_, *current_key_frame_);
   bool rotate_done =
    !stl_util::ContainsKey(rotate_frames_, *current_key_frame_);
   bool scale_done =
    !stl_util::ContainsKey(scale_frames_, *current_key_frame_);

   for (; next_key_frame != key_frames_.end(); ++next_key_frame) {
      if (!translate_done &&
          stl_util::ContainsKey(translate_frames_, *next_key_frame)) {

#ifdef TEST_ANIMATION
         c + s("setting translation, frame=%d", *current_key_frame_);
         c + s("will take: %lf seconds",
            duration(*current_key_frame_, *next_key_frame));
         glm_util::Print(translate_frames_[*next_key_frame].translate);
#endif
         entity_->set_position(translate_frames_[*next_key_frame].translate,
            duration(*current_key_frame_, *next_key_frame));
         translate_done = true;
      }
      if (!rotate_done && stl_util::ContainsKey(rotate_frames_, *next_key_frame)) {
#ifdef TEST_ANIMATION
         c + s("setting rotation, frame=%d", *current_key_frame_);
         c + s("angle=%lf", rotate_frames_[*next_key_frame].rotate.angle);
         glm_util::Print(rotate_frames_[*next_key_frame].rotate.axis);
         c + s("will take: %lf seconds",
            duration(*current_key_frame_, *next_key_frame));
#endif
         entity_->set_rotation(rotate_frames_[*next_key_frame].rotate,
            duration(*current_key_frame_, *next_key_frame));
         rotate_done = true;
      }
      if (!scale_done && stl_util::ContainsKey(scale_frames_, *next_key_frame)) {
#ifdef TEST_ANIMATION
         c + s("setting scale, frame=%d", *current_key_frame_);
         glm_util::Print(scale_frames_[*next_key_frame].scale);
         c + s("will take: %lf seconds",
            duration(*current_key_frame_, *next_key_frame));
#endif
         entity_->set_scale(scale_frames_[*next_key_frame].scale,
            duration(*current_key_frame_, *next_key_frame));
         scale_done = true;
      }
   }

   ++current_key_frame_;
   EventLoop::Instance()->StartNewTimer(this, "", duration_until_next_key_frame);
#ifdef TEST_ANIMATION
   c + s("//////////////////KEYFRAME END");
#endif
}

void Animation::SwapEntity(const std::string& e) {
}

void Animation::StartAnimation() {
   if (key_frames_.size() == 0) {
#ifdef TEST_ANIMATION
      exit(0);
#endif
      return;
   }
   c + s("starting animation %s", name_.c_str());

   // Make this animation a parent of its children.
   entity_ = new EntityComposite(glm::vec3(), Rotation(), glm::vec3(1.0f),
         name_);
   g_scene->Add(entity_);
   for (vector<string>::iterator it = children_.begin();
        it != children_.end(); ++it) {
      g_scene->Remove(g_entities[*it]);
      entity_->Add(g_entities[*it]);
   }
   for (map<int, LoadAnimationFrame>::iterator
        it = loaded_animation_frames_.begin();
        it != loaded_animation_frames_.end(); ++it) {
      g_scene->Remove(g_animations[it->second.animation]->entity());
      entity_->Add(g_animations[it->second.animation]->entity());
   }

   // Set the animation to the initial transforms/display.
   current_key_frame_ = key_frames_.find(0);
   if (stl_util::ContainsKey(display_frames_, *current_key_frame_))
      entity_->set_should_draw(display_frames_[*current_key_frame_].display);
   if (stl_util::ContainsKey(translate_frames_, *current_key_frame_))
      entity_->set_position(translate_frames_[*current_key_frame_].translate);
   if (stl_util::ContainsKey(rotate_frames_, *current_key_frame_))
      entity_->set_rotation(rotate_frames_[*current_key_frame_].rotate);
   if (stl_util::ContainsKey(scale_frames_, *current_key_frame_))
      entity_->set_scale(scale_frames_[*current_key_frame_].scale);
   // Start the animation.
   OnExpiration("");
}
