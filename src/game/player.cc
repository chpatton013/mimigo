#include "player.h"
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

Player::Player(Planet* planet) :
   transition_planet_(planet),
   planet_rotater_(planet->center(), planet->radius(), position_),
   is_jumping_(false),
   observer_(NULL)
{
   LoadMetaDataFromFile("player.config");
   mesh_ = new SceneNode("player");
   RootNode::Instance()->AddChild(mesh_);
   mesh_->AddChild(SceneNode::Get("bunny"));
   rotation_.axis = glm::vec3(0.0f, 0.0f, 1.0f);
   left_right_rotation_.axis = glm::vec3(0.0f, 1.0f, 0.0f);
   TransitionTo(planet);
}

// static
void Player::RotationEndCallback(void* p) {
   Player* player = static_cast<Player*>(p);
   player->attach_planet(player->transition_planet_);
}

void Player::StartMovingCounterClockwiseAroundAttachedPlanet() {
   planet_rotater_.StartRotatingCounterClockwise(kMoveSpeed);
   left_right_rotation_.angle = 0.0f;
}

void Player::StartMovingClockwiseAroundAttachedPlanet() {
   planet_rotater_.StartRotatingClockwise(kMoveSpeed);
   left_right_rotation_.angle = 180.0f;
}

bool Player::IsTopSideOfPlanet() {
   return planet_rotater_.IsOnTopside();
}

bool Player::IsRightSideOfPlanet() {
   return planet_rotater_.IsOnRightside();
}

void Player::StartMovingUpAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (attached_planet_->is_small_planet()) {
      if (IsRightSideOfPlanet())
         StartMovingCounterClockwiseAroundAttachedPlanet();
      else
         StartMovingClockwiseAroundAttachedPlanet();
   } else {
      planet_rotater_.StartMoving(glm::normalize(position_ - camera_pos), kMoveSpeed);
   }
}

void Player::StartMovingDownAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (attached_planet_->is_small_planet()) {
      if (IsRightSideOfPlanet())
         StartMovingClockwiseAroundAttachedPlanet();
      else
         StartMovingCounterClockwiseAroundAttachedPlanet();
   } else {
      planet_rotater_.StartMoving(glm::normalize(camera_pos - position_), kMoveSpeed);
   }
}

void Player::StartMovingLeftAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (attached_planet_->is_small_planet()) {
      if (IsTopSideOfPlanet())
         StartMovingCounterClockwiseAroundAttachedPlanet();
      else
         StartMovingClockwiseAroundAttachedPlanet();
   } else {
   }
}

void Player::StartMovingRightAroundAttachedPlanet(const glm::vec3& camera_pos) {
   if (attached_planet_->is_small_planet()) {
      if (IsTopSideOfPlanet())
         StartMovingClockwiseAroundAttachedPlanet();
      else
         StartMovingCounterClockwiseAroundAttachedPlanet();
   } else {
   }
}

void Player::Jump() {
   planet_rotater_.Jump(kJumpHeight);
}

void Player::StopMoving() {
   planet_rotater_.StopRotating();
}

bool Player::EntersGravityFieldOf(Planet* planet) {
   if (planet == attached_planet_)
      return false;

   if (is_jumping() && planet->PositionWithinGravityField(position_))
      return true;

   return false;
}

void Player::UpdateMesh() {
   glm::mat4 transform;
   transform *= glm::translate(position_);
   transform *= glm::rotate(rotation_.angle, rotation_.axis);
   transform *= glm::rotate(left_right_rotation_.angle,
                            left_right_rotation_.axis);
   mesh_->set_transformation(transform);
}

glm::vec3 Player::up() const {
   return glm::normalize(position_ - attached_planet_->center());
}

glm::vec3 Player::facing() const {
   return glm::normalize(position_ - attached_planet_->center());
}

void Player::Update() {
   planet_rotater_.Update(position_, rotation_, &is_jumping_);
   rotater_.Update(rotation_.angle);
   UpdateMesh();
   if (observer_)
      observer_->OnPlayerMove(position_, up(), facing());
}

inline
float angle_of(const glm::vec3& vec) {
   return 180.0f * std::atan2(vec.y, vec.x) / (atan(1) * 4);
}

void Player::RotateBottomToward(Planet* planet) {
   rotater_.Move(rotation_.angle,
         angle_of(position_ - planet->center()) - 90.0f - rotation_.angle,
         kRotateTime, RotationEndCallback, this);
}

void Player::TransitionTo(Planet* planet) {
   RotateBottomToward(planet);
   transition_planet_ = planet;
}
