#include "small_planet_mover.h"
#include <sstream>
#include <fstream>

static float kMoveSpeed = 0.0f;
static float kJumpHeight = 0.0f;
static float kRotateTime = 0.0f;

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
      else if (id == "jump_height")
         stream >> kJumpHeight;
      else if (id == "rotate_time")
         stream >> kRotateTime;
   }
}

SmallPlanetMover::SmallPlanetMover(Planet* planet, glm::vec3& position,
                                   Rotation& rotation) :
   planet_(planet),
   position_(position),
   rotation_(rotation),
   planet_rotater_(NULL),
   is_jumping_(false)
{
   LoadMetaDataFromFile("player.config");
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void SmallPlanetMover::RotateBottomTowardPlanet() {
   rotation_.angle = angle_of(position_ - planet_->center()) - 90.0f;
}

void SmallPlanetMover::MoveCounterClockwiseAroundPlanet() {
   planet_rotater_->StartRotatingCounterClockwise(kMoveSpeed);
}

void SmallPlanetMover::MoveClockwiseAroundPlanet() {
   planet_rotater_->StartRotatingClockwise(kMoveSpeed);
}

void SmallPlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   if (planet_rotater_)
      delete planet_rotater_;
   planet_rotater_ = new PlanetRotater(planet->center(), planet->radius(), position_);
}

void SmallPlanetMover::Update() {
   planet_rotater_->Update(position_, rotation_, &is_jumping_);
}

void SmallPlanetMover::StopMoving() {
   planet_rotater_->StopRotating();
}

void SmallPlanetMover::Jump() {
   planet_rotater_->Jump(kJumpHeight);
}
