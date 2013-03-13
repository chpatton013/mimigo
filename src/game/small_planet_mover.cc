#include "small_planet_mover.h"
#include "player.h"
#include <sstream>
#include <fstream>

static float kMoveSpeed = 0.0f;
static float kJumpSpeed = 0.0f;
static float kJumpSlowdown = 0.0f;
static float kJumpSlowdownHeld = 0.0f;
static float kRotateTime = 0.0f;
static float kThetaAcceleration = 0.0f;
static float kThetaSpeed = 0.0f;

const int SmallPlanetMover::JUMP_THRESHOLD = 250;
const int SmallPlanetMover::MAX_JUMP_LEVEL = 3;

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

SmallPlanetMover::SmallPlanetMover(Planet* planet, PlayerObserver* observer) :
   dir_facing_(CW),
   move_dir_(NONE),
   planet_(planet),
   jump_speed_(kJumpSpeed),
   theta_(0.0f),
   theta_speed_(0.0f),
   jump_level_(0),
   is_jumping_(false),
   observer_(observer)
{
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   LoadMetaDataFromFile("player.config");
}

void SmallPlanetMover::MoveUp() {
   if (theta_ > 90.0f && theta_ <= 270.0f) move_dir_ = CW;
   else move_dir_ = CCW;
}

void SmallPlanetMover::MoveDown() {
   if (theta_ > 90.0f && theta_ <= 270.0f) move_dir_ = CCW;
   else move_dir_ = CW;
}

void SmallPlanetMover::MoveLeft() {
   dir_facing_ = CCW;
   move_dir_ = CCW;
}
void SmallPlanetMover::MoveRight() {
   dir_facing_ = CW;
   move_dir_ = CW;
}

void SmallPlanetMover::StopMoveUp() { move_dir_ = NONE;  }
void SmallPlanetMover::StopMoveDown() { move_dir_ = NONE; }
void SmallPlanetMover::StopMoveLeft() { move_dir_ = NONE; }
void SmallPlanetMover::StopMoveRight() { move_dir_ = NONE; }

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

   if (dir_facing_ == CCW){
      transform *= glm::rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
   } else if (dir_facing_ == CW){
      transform *= glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
   }

   SceneNode::Get("player")->set_transformation(transform);
}

inline float radians(float degrees) {
   return degrees * M_PI / 180.0f;
}

const glm::vec3 SmallPlanetMover::position() const {
   return planet_->center() + glm::vec3(
         radius_ * std::cos(radians(theta_)),
         radius_ * std::sin(radians(theta_)),
         0.0f);
}

void SmallPlanetMover::FallToPlanet() {
   is_jumping_ = false;
   is_falling_ = true;
}

void SmallPlanetMover::set_planet(Planet* planet) {
   if (planet_)
      theta_ = angle_of(position() - planet->center());
   else
      theta_ = 30.0f;
   planet_ = planet;
   is_jumping_ = false;
   jump_speed_ = 0.0f;
   is_falling_ = true;
   RotateBottomTowardPlanet();
   FallToPlanet();
   radius_ = planet->gravity_radius() - planet->radius();
   if (observer_)
      observer_->OnPlayerSwitchPlanets(planet);
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
   if (theta_speed > 0.0f)
      return accelerate_clockwise(0.0f, theta_speed);
   else if (theta_speed < 0.0f)
      return accelerate_counterclockwise(0.0f, theta_speed);
   else
      return theta_speed;
}

bool SmallPlanetMover::should_move_counterclockwise() const {
   return move_dir_ == CCW;
}

bool SmallPlanetMover::should_move_clockwise() const {
   return move_dir_ == CW;
}

inline
float jump_speed() {
   return kThetaSpeed * 0.5f;
}

float SmallPlanetMover::max_theta_speed() const {
   if (is_jumping_ || is_falling_) {
      return jump_speed() * jump_modifier();
   } else {
      return kThetaSpeed;
   }
}

void SmallPlanetMover::set_theta(float theta) {
   theta_ = wrap_angle(theta);
}

void SmallPlanetMover::Update() {
   if (is_jumping_ || is_falling_) {
      if (jump_held_ && jump_speed_ > 0.0f) {
         jump_speed_ -= kJumpSlowdownHeld;
      } else {
         jump_speed_ -= kJumpSlowdown;
      }

      if (jump_speed_ <= 0.0f) {
         is_jumping_ = false;
         is_falling_ = true;
      }

      radius_ += jump_speed_ * jump_modifier();
      if (radius_ <= planet_->radius() + 0.125f) {
         jump_speed_ = kJumpSpeed;
         radius_ = planet_->radius() + 0.125f;
         is_falling_ = false;
         jump_clock_.start();
      }
   }

   if (should_move_clockwise())
      theta_speed_ = accelerate_clockwise(max_theta_speed(), theta_speed_);
   else if (should_move_counterclockwise())
      theta_speed_ = accelerate_counterclockwise(max_theta_speed(), theta_speed_);
   else
      theta_speed_ = decelerate(theta_speed_);
   set_theta(theta_ + (theta_speed_ / planet_->radius()));
   RotateBottomTowardPlanet();

   UpdateMeshTransform();
   if (observer_)
      observer_->OnPlayerMove(position(), glm::vec3(), glm::vec3());
}

void SmallPlanetMover::StopMoving() {
}

void SmallPlanetMover::Jump() {
   if (is_jumping_)
      return;

   jump_clock_.stop();
   calc_jump_level();

   is_jumping_ = true;
   jump_held_ = true;
}

void SmallPlanetMover::ReleaseJump() {
   jump_held_ = false;
}

void SmallPlanetMover::OnExpiration(const std::string& event) {
   assert(true || event.size());
}

void SmallPlanetMover::calc_jump_level() {
   int difference = jump_clock_.get_milli();
   int delta = difference / JUMP_THRESHOLD;

   // Increase jump level if you are jumping fast enough...
   if (delta == 0 && jump_level_ < MAX_JUMP_LEVEL) {
      ++jump_level_;
   // or reduce jump level by the number of thresholds that have passed...
   } else if (jump_level_ > delta) {
      jump_level_ -= delta;
   // or just reset jump level if you are really slow.
   } else {
      jump_level_ = 0;
   }
}
float SmallPlanetMover::jump_modifier() const {
   return jump_level_ * 2.0f + 1.0f;
}
