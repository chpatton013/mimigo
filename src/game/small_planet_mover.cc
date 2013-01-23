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
float adjust_angle(float &val) {
   while (val < 0.0f)
      val += 360.0f;
   while (val > 360.0f)
      val -= 360.0f;
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

   float max_theta = is_jumping_ || is_falling_ ? kThetaSpeed / 2 : kThetaSpeed;
   // Clockwise
   if ((move_dir_ & UP) == UP && (theta_ > 100.0f && theta_ < 270.0f) ||
       (move_dir_ & LEFT) == LEFT && theta_ > 190.0f ||
       (move_dir_ & DOWN) == DOWN && (theta_ > 280.0f || theta_ < 90.0f) ||
       (move_dir_ & RIGHT) == RIGHT && (theta_ > 10.0f && theta_ < 180.0f)) {
      theta_speed_ = std::max(-max_theta, theta_speed_ - kThetaAcceleration);
   }
   // Counter-Clockwise
   else if ((move_dir_ & UP) == UP && (theta_ > 270.0f || theta_ < 80.0f) ||
            (move_dir_ & LEFT) == LEFT && theta_ < 170.0f ||
            (move_dir_ & DOWN) == DOWN && (theta_ < 260.0f && theta_ > 90.0f) ||
            (move_dir_ & RIGHT) == RIGHT && (theta_ > 180.0f && theta_ < 350.0f)) {
      theta_speed_ = std::min(max_theta, theta_speed_ + kThetaAcceleration);
   } else {
      if (theta_speed_ > 0.0f)
         theta_speed_ = std::max(0.0f, theta_speed_ - kThetaAcceleration);
      else
         theta_speed_ = std::min(0.0f, theta_speed_ + kThetaAcceleration);
   }
   theta_ += theta_speed_;
   adjust_angle(theta_);

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
