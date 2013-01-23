#include "small_planet_mover.h"
#include <sstream>
#include <fstream>

static float kMoveSpeed = 0.0f;
static float kJumpSpeed = 0.0f;
static float kJumpSlowdown = 0.0f;
static float kJumpSlowdownHeld = 0.0f;
static float kRotateTime = 0.0f;
static float kThetaAcceleration = 0.0f;
static float kThetaSpeed = 0.0f;

void LoadMetaDataFromFile(const std::string& filename) {
   std::ifstream in;
   in.open(filename.c_str());

   std::string line;
   while (getline(in, line)) {
      std::istringstream stream(line);
      std::string id;
      stream >> id;
      if (id == "move_speed")
         stream >> kMoveSpeed;
      else if (id == "jump_start_speed")
         stream >> kJumpSpeed;
      else if (id == "jump_speed_slowdown")
         stream >> kJumpSlowdown;
      else if (id == "jump_speed_slowdown_held")
         stream >> kJumpSlowdownHeld;
      else if (id == "rotate_time")
         stream >> kRotateTime;
      else if (id == "theta_acceleration")
         stream >> kThetaAcceleration;
      else if (id == "max_theta_speed")
         stream >> kThetaSpeed;
   }
}

SmallPlanetMover::SmallPlanetMover(Planet* planet) :
   planet_(planet),
   jump_speed_(kJumpSpeed),
   theta_(0.0f),
   theta_speed_(0.0f),
   move_dir_(0),
   is_jumping_(false)
{
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   LoadMetaDataFromFile("player.config");
}

void SmallPlanetMover::MoveUp() { move_dir_ |= UP; }
void SmallPlanetMover::MoveDown() { move_dir_ |= DOWN; }
void SmallPlanetMover::MoveLeft() { move_dir_ |= LEFT; }
void SmallPlanetMover::MoveRight() { move_dir_ |= RIGHT; }

void SmallPlanetMover::StopMoveUp() { move_dir_ &= ~UP; }
void SmallPlanetMover::StopMoveDown() { move_dir_ &= ~DOWN; }
void SmallPlanetMover::StopMoveLeft() { move_dir_ &= ~LEFT; }
void SmallPlanetMover::StopMoveRight() { move_dir_ &= ~RIGHT; }

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

inline
float wrap_angle(float val) {
   while (val < 0.0f)
      val += 360.0f;
   while (val > 360.0f)
      val -= 360.0f;
   return val;
}

void SmallPlanetMover::RotateBottomTowardPlanet() {
   xy_rotation_.angle = theta_ - 90.0f;
}

void SmallPlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform;
   transform *= glm::translate(position());
   transform *= glm::rotate(xy_rotation_.angle, xy_rotation_.axis);
   transform *= glm::rotate(xz_rotation_.angle, xz_rotation_.axis);
   SceneNode::Get("player")->set_transformation(transform);
}

inline float radians(float degrees) {
   return degrees * (atan(1)*4.0) / 180.0f;
}

const glm::vec3 SmallPlanetMover::position() const {
   return planet_->center() + glm::vec3(
         radius_ * std::cos(radians(theta_)),
         radius_ * std::sin(radians(theta_)),
         0);
}

void SmallPlanetMover::FallToPlanet() {
   is_jumping_ = false;
   is_falling_ = true;
}

void SmallPlanetMover::set_planet(Planet* planet) {
   if (planet_)
      theta_ = angle_of(position() - planet->center());
   else
      theta_ = 0.0f;
   planet_ = planet;
   is_jumping_ = false;
   jump_speed_ = 0.0f;
   is_falling_ = true;
   RotateBottomTowardPlanet();
   FallToPlanet();
}

inline bool has_bits(unsigned short byte, unsigned short bits) {
   return (byte & bits) == bits;
}

inline float destination_angle(unsigned short move_dir) {
   if (has_bits(move_dir, UP | RIGHT)) return 45;
   if (has_bits(move_dir, UP | LEFT)) return 135;
   if (has_bits(move_dir, DOWN | LEFT)) return 225;
   if (has_bits(move_dir, DOWN | RIGHT)) return 315;

   if (has_bits(move_dir, RIGHT)) return 0;
   if (has_bits(move_dir, UP)) return 90;
   if (has_bits(move_dir, LEFT)) return 180;
   if (has_bits(move_dir, DOWN)) return 270;
}

inline
bool angle_is_between(float a, float between, float b) {
   assert(b > a);
   a = wrap_angle(a);
   b = wrap_angle(b);
   between = wrap_angle(between);

   return a < b ? a < between && between < b : between > a || between < b;
}

inline
float accelerate_clockwise(float max_speed, float theta_speed) {
   return std::max(-max_speed, theta_speed - kThetaAcceleration);
}

inline
float accelerate_counterclockwise(float max_speed, float theta_speed) {
   return std::min(max_speed, theta_speed + kThetaAcceleration);
}

inline
float decelerate(float theta_speed) {
   if (theta_speed > 0.0f) {
      return accelerate_clockwise(0.0f, theta_speed);
   } else if (theta_speed < 0.0f) {
      return accelerate_counterclockwise(0.0f, theta_speed);
   }
   return theta_speed;
}

void SmallPlanetMover::Update() {
   RotateBottomTowardPlanet();
   //TODO: time-based motion
   if (is_jumping_ || is_falling_) {
      if (jump_held_ && jump_speed_ > 0.0f)
         jump_speed_ -= kJumpSlowdownHeld;
      else
         jump_speed_ -= kJumpSlowdown;
      if (jump_speed_ <= 0.0f) {
         is_jumping_ = false;
         is_falling_ = true;
      }
      radius_ += jump_speed_;
      if (radius_ <= planet_->radius()) {
         jump_speed_ = kJumpSpeed;
         radius_ = planet_->radius();
         is_falling_ = false;
      }
   }

   float max_theta_speed = is_jumping_ || is_falling_ ? kThetaSpeed / 2 : kThetaSpeed;
   if (is_moving()) {
      float dest_angle = destination_angle(move_dir_);
      if (angle_is_between(dest_angle + 5, theta_, dest_angle + 180))
         theta_speed_ = accelerate_clockwise(max_theta_speed, theta_speed_);
      else if (angle_is_between(dest_angle - 180, theta_, dest_angle - 5))
         theta_speed_ = accelerate_counterclockwise(max_theta_speed, theta_speed_);
      else
         theta_speed_ = decelerate(theta_speed_);
   }
   else {
      theta_speed_ = decelerate(theta_speed_);
   }
   theta_ += theta_speed_;
   theta_ = wrap_angle(theta_);

   UpdateMeshTransform();
}

void SmallPlanetMover::StopMoving() {
}

void SmallPlanetMover::Jump() {
   if (is_jumping_)
      return;

   is_jumping_ = true;
   jump_held_ = true;
}

void SmallPlanetMover::ReleaseJump() {
   jump_held_ = false;
}

void SmallPlanetMover::OnExpiration(const std::string& event) {
}
