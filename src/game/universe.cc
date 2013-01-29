#include "universe.h"
#include "sdl/sdl_event_loop.h"
#include "asteroid.h"
#include "swing_asteroid.h"
#include "player.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include "small_planet_camera.h"
#include "large_planet_camera.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string asteroid_event_name(const std::string &id, int planet_id, float angle) {
   std::string event_name;
   std::ostringstream stream(event_name);
   stream << id << " " << planet_id << " " << angle;
   return stream.str();
}

void Universe::ParseAsteroidFile() {
   std::ifstream in("asteroids.lvl");
   bool swing_asteroid = false;

   std::string line;
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/sphere.obj");
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else if (line[0] == 'A') {
         swing_asteroid = false;
      }
      else if (line[0] == 'S') {
         swing_asteroid = true;
      }
      else {
         std::string id;
         int planet_id;
         float theta, delay, angle;
         stream >> id;
         stream >> delay;
         stream >> planet_id;
         --planet_id;
         stream >> angle;
         if (!swing_asteroid) {
            RootNode::Instance()->AddChild(new EntityComponentNode("asteroid" + id, sphere));
            SceneNode::Get("asteroid" + id)->set_visible(false);
            EventLoop::Instance()->StartNewTimer(this, asteroid_event_name("asteroid" + id, planet_id, angle), delay);
         } else {
            RootNode::Instance()->AddChild(new EntityComponentNode("swingasteroid" + id, sphere));
            SceneNode::Get("swingasteroid" + id)->set_visible(false);
            EventLoop::Instance()->StartNewTimer(this, asteroid_event_name("swingasteroid" + id, planet_id, angle), delay);
         }
      }
   }
}

void ParsePlanetFile(const std::string& filename, std::vector<Planet*> *planets) {
   std::ifstream in(filename.c_str());

   PlanetType planet_type = PLANET_TYPE_SMALL;

   std::string line;
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/sphere.obj");
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else if (line[0] == 'S') {
         planet_type = PLANET_TYPE_SMALL;
      }
      else if (line[0] == 'L') {
         planet_type = PLANET_TYPE_LARGE;
      }
      else {
         std::string id;
         glm::vec3 position;
         float radius, gravity_radius;
         stream >> id;
         stream >> position.x;
         stream >> position.y;
         stream >> position.z;
         stream >> radius;
         stream >> gravity_radius;
         RootNode::Instance()->AddChild(new EntityComponentNode("planet" + id, sphere));
         planets->push_back(new Planet(planet_type, id, position, radius, gravity_radius));
      }
   }
}

void Universe::LoadInPlanets() {
   ParsePlanetFile("planets.lvl", &planets_);
}

Universe::Universe() :
   game_play_type_(GAME_PLAY_SMALL)
{
   camera_ = new SmallPlanetCamera();
   LoadInPlanets();
   ParseAsteroidFile();
   player_ = new Player(planets_[0], camera_);
   PlayerEntersGravityFieldOf(planets_[0]);
}

void Universe::OnExpiration(const std::string& event_name) {
   if (event_name.find("asteroid") == 0) {
      std::istringstream stream(event_name);
      std::string id;
      float angle;
      int planet_id;
      stream >> id;
      stream >> planet_id;
      stream >> angle;
      asteroids_.push_back(new Asteroid(planets_[planet_id], angle, id));
   } else if (event_name.find("swingasteroid") == 0) {
      std::istringstream stream(event_name);
      std::string id;
      float angle;
      int planet_id;
      int clockwise = 0;
      stream >> id;
      stream >> planet_id;
      stream >> angle;
      stream >> clockwise;
      std::cout << clockwise << std::endl;
      swing_asteroids_.push_back(new SwingAsteroid(planets_[planet_id], angle, id, clockwise != 0));
   }
}

bool Universe::PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet) {
   return planet->is_large_planet();
}

void Universe::UseLargePlanetCamera() {
   delete camera_;
   camera_ = new LargePlanetCamera();
   player_->set_large_planet_observer(camera_);
}

void Universe::SwitchToLargePlanetGamePlay() {
   UseLargePlanetCamera();
   game_play_type_ = GAME_PLAY_LARGE;
}

void Universe::PlayerEntersGravityFieldOf(Planet* planet) {
   player_->TransitionTo(planet);
   if (PlayerTransitionsFromSmallPlanetToLargePlanet(planet)) {
      SwitchToLargePlanetGamePlay();
   }
}

void Universe::CheckPlayerChangesGravityFields() {
   if (player_->is_jumping()) {
      for (std::vector<Planet*>::iterator it = planets_.begin();
            it != planets_.end(); ++it) {
         if (player_->EntersGravityFieldOf(*it)) {
            PlayerEntersGravityFieldOf(*it);
            break; // Since we found a change already, we don't check the rest.
         }
      }
   }
}

template <class T>
void Universe::UpdateAsteroids(std::vector<T>& asteroids) {
   std::vector<T> to_remove;
   for (typename std::vector<T>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
      if (!(*it)->Update())
         to_remove.push_back(*it);
   for (typename std::vector<T>::iterator it = to_remove.begin(); it != to_remove.end(); ++it)
      delete *it;
   stl_util::RemoveAllOf(asteroids, to_remove);
}

void Universe::Update() {
   camera_->Update();
   player_->Update();

   UpdateAsteroids(asteroids_);
   UpdateAsteroids(swing_asteroids_);

   CheckPlayerChangesGravityFields();
}

void Universe::Draw() {
   camera_->SetView();
   RootNode::Instance()->Draw();
}

//DEBUG METHODS
void Universe::OnCameraDownDown() {}
void Universe::OnCameraUpDown() {}
//DEBUG METHODS

void Universe::OnLeftButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnLeftButtonDown();
   else {
      player_->TurnLeft();
   }
}

void Universe::OnRightButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnRightButtonDown();
   else {
      player_->TurnRight();
   }
}

void Universe::OnUpButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnUpButtonDown();
   else {
      player_->MoveForward();
   }
}

void Universe::OnDownButtonDown() {
   if (is_small_planet_gameplay())
      player_->OnDownButtonDown();
   else {
      player_->MoveBackward();
   }
}

void Universe::OnLeftButtonUp()  { player_->OnLeftButtonUp(); }
void Universe::OnRightButtonUp() { player_->OnRightButtonUp(); }
void Universe::OnUpButtonUp()    { player_->OnUpButtonUp(); }
void Universe::OnDownButtonUp()  { player_->OnDownButtonUp(); }

void Universe::OnJumpButtonDown() {
   player_->Jump();
}
void Universe::OnJumpButtonUp() {
   player_->ReleaseJump();
}
