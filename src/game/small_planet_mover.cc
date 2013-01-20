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

SmallPlanetMover::SmallPlanetMover(Planet* planet) :
   planet_(planet),
   planet_rotater_(NULL),
   is_jumping_(false)
{
   xy_rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   xz_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   LoadMetaDataFromFile("player.config");
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void SmallPlanetMover::MoveUp(const glm::vec3& camera_pos) {
   if (IsRightSideOfPlanet())
      MoveCounterClockwiseAroundPlanet();
   else
      MoveClockwiseAroundPlanet();
}

void SmallPlanetMover::MoveDown(const glm::vec3& camera_pos) {
   if (IsRightSideOfPlanet())
      MoveClockwiseAroundPlanet();
   else
      MoveCounterClockwiseAroundPlanet();
}

void SmallPlanetMover::MoveLeft(const glm::vec3& camera_pos) {
   if (IsTopSideOfPlanet())
      MoveCounterClockwiseAroundPlanet();
   else
      MoveClockwiseAroundPlanet();
}

void SmallPlanetMover::MoveRight(const glm::vec3& camera_pos) {
   if (IsTopSideOfPlanet())
      MoveClockwiseAroundPlanet();
   else
      MoveCounterClockwiseAroundPlanet();
}

void SmallPlanetMover::RotateBottomTowardPlanet() {
   xy_rotation_.angle = angle_of(position_ - planet_->center()) - 90.0f;
}

void SmallPlanetMover::UpdateMeshTransform() const {
   glm::mat4 transform;
   transform *= glm::translate(position_);
   transform *= glm::rotate(xy_rotation_.angle, xy_rotation_.axis);
   transform *= glm::rotate(xz_rotation_.angle, xz_rotation_.axis);
   SceneNode::Get("player")->set_transformation(transform);
}

void SmallPlanetMover::MoveCounterClockwiseAroundPlanet() {
   planet_rotater_->StartRotatingCounterClockwise(kMoveSpeed);
   xz_rotation_.angle = 0.0f;
}

void SmallPlanetMover::MoveClockwiseAroundPlanet() {
   planet_rotater_->StartRotatingClockwise(kMoveSpeed);
   xz_rotation_.angle = 180.0f;
}

void SmallPlanetMover::set_planet(Planet* planet) {
   planet_ = planet;
   if (planet_rotater_)
      delete planet_rotater_;
   planet_rotater_ = new PlanetRotater(planet->center(), planet->radius(), position_);
}

void SmallPlanetMover::Update() {
   planet_rotater_->Update(position_, xy_rotation_, &is_jumping_);
}

void SmallPlanetMover::StopMoving() {
   planet_rotater_->StopRotating();
}

void SmallPlanetMover::Jump() {
   planet_rotater_->Jump(kJumpHeight);
}
