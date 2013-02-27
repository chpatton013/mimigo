#include "universe.h"
#include "sdl/sdl_event_loop.h"
#include "asteroid.h"
#include "checkpoint.h"
#include "swing_asteroid.h"
#include "player.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include "small_planet_camera.h"
#include "large_planet_camera.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <utility>


std::string asteroid_event_name(const std::string &id, int planet_id, float angle) {
   std::string event_name;
   std::ostringstream stream(event_name);
   stream << id << " " << planet_id << " " << angle;
   return stream.str();
}
static inline std::string &ltrim(std::string &s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   return s;
}

static inline std::string &rtrim(std::string &s) {
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
   return ltrim(rtrim(s));
}

void Universe::ParseAsteroidFile() {
   std::ifstream in("asteroids.lvl");
   bool swing_asteroid = false;

   std::string line;
   std::string event("NULL");
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/asteroid.obj");
   EntityComponent* fish = LoadEntityComponentFromOBJ("meshes/puffer3.obj");
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
      else if (line[0] == 'E') {
         // It's an asteroid event
         stream >> event;
         getline(stream, event);
         trim(event);
      }
      else {
         std::string id;
         int planet_id;
         float delay, angle;
         stream >> id;
         stream >> delay;
         stream >> planet_id;
         --planet_id;
         stream >> angle;

         std::string full_id = (swing_asteroid ? "swingasteroid" : "asteroid") + id;


         if (id == "3") {
            EntityComponentNode* meshy = new
             EntityComponentNode(full_id, fish);
            meshy->apply_transformation(glm::scale(glm::mat4(), glm::vec3(0.1)));
            RootNode::Instance()->AddChild(meshy);
         } else {
            RootNode::Instance()->AddChild(new
             EntityComponentNode(full_id, sphere));
         }

         SceneNode::Get(full_id)->set_visible(false);

         if (event == "NULL") {
            EventLoop::Instance()->StartNewTimer(
               this,
               asteroid_event_name(full_id, planet_id, angle),
               delay
            );
         } else {
            event_map_[event].push_back(Event(
               asteroid_event_name(full_id, planet_id, angle),
               delay
            ));
         }
      }
   }
}

void ParsePlanetFile(const std::string& filename, std::vector<Planet*> *planets) {
   std::ifstream in(filename.c_str());

   PlanetType planet_type = PLANET_TYPE_SMALL;

   std::string line;
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/sphere.obj");
   EntityComponent* tree = LoadEntityComponentFromOBJ("meshes/tree3.obj");
   EntityComponent* shark = LoadEntityComponentFromOBJ("meshes/shark.obj");
   EntityComponent* adobe = LoadEntityComponentFromOBJ("meshes/adobe.obj");
   EntityComponent* house = LoadEntityComponentFromOBJ("meshes/house.obj");
   EntityComponent* cactus = LoadEntityComponentFromOBJ("meshes/cactus.obj");
   EntityComponent* flower = LoadEntityComponentFromOBJ("meshes/flower3.obj");
   EntityComponent* coral = LoadEntityComponentFromOBJ("meshes/coral.obj");
   EntityComponent* asteroid = LoadEntityComponentFromOBJ("meshes/asteroid.obj");

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
   RootNode::Instance()->AddChild(new EntityComponentNode("tree1", tree));
   new Assets("tree", "1", glm::vec3(-10.0, 0.4, 0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 0.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("tree2", coral));
   new Assets("tree", "2", glm::vec3(-4.5, -1.5, 0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 0.0);

  RootNode::Instance()->AddChild(new EntityComponentNode("adobe3", adobe));
  new Assets("adobe", "3", glm::vec3(-7.8,  -0.15,  0.0), glm::vec3(0.7), glm::vec3(0.0, 0.0, 1.0), 180.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("house4", house));
   new Assets("house", "4", glm::vec3(-10.8, -0.5, 0), glm::vec3(0.7), glm::vec3(0.0, 0.0, 1.0), 90.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("cactus5", cactus));
   new Assets("cactus", "5", glm::vec3(-7.8,  1.45,  0.0), glm::vec3(0.7), glm::vec3(1.0, 1.0, 1.0), 0.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("flower7", flower));
   new Assets("flower", "7", glm::vec3(-6.0, .2, 0), glm::vec3(0.25), glm::vec3(1.0, 1.0, 1.0), 0.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("flower8", flower));
   new Assets("flower", "8", glm::vec3(-5.5, 0, 0), glm::vec3(0.25), glm::vec3(1.0, 1.0, 1.0), 0.0);

   RootNode::Instance()->AddChild(new EntityComponentNode("flower9", flower));
   new Assets("flower", "9", glm::vec3(-6.5, -.1, 0), glm::vec3(0.25), glm::vec3(1.0, 1.0, 1.0), 0.0);

RootNode::Instance()->AddChild(new EntityComponentNode("cactus10", cactus));
   new Assets("cactus", "10", glm::vec3(-8.15,  0.8,  0.55), glm::vec3(0.3), glm::vec3(0.5, 0.5, 0.5), 45.0);

RootNode::Instance()->AddChild(new EntityComponentNode("rock11", asteroid));
   new Assets("rock", "11", glm::vec3(-7.5,  0.5,  0.45), glm::vec3(0.3), glm::vec3(0.5, 0.5, 0.0), 45.0);

RootNode::Instance()->AddChild(new EntityComponentNode("shark12", shark));
   new Assets("shark", "12", glm::vec3(-2.7,  -0.75,  0.0), glm::vec3(1.0), glm::vec3(0.5, 0.5, 0.0), 45.0);
}

void ParseCheckPointsFile(std::vector<Planet*> planets) {
   std::ifstream in("checkpoints.lvl");

	std::string id;
         int planet_id;
         float angle;
std::string full_id;


   std::string line;
   EntityComponent* flag = LoadEntityComponentFromOBJ("meshes/flag3.obj");
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else {
         stream >> id;
         stream >> planet_id;
         --planet_id;
         stream >> angle;

         full_id = "checkpoint" + id;

	std::cout << full_id;

            RootNode::Instance()->AddChild(new
             EntityComponentNode(full_id, flag));

        SceneNode::Get(full_id)->set_visible(true);
      }
   }

SpatialManager::Instance()->AddEntity(new CheckPoint(planets[planet_id], planet_id,  angle, full_id));
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
   ParseCheckPointsFile(planets_);
   player_ = new Player(planets_[0], camera_);

   ps = new ParticleSystem(15);
   PlayerEntersGravityFieldOf(planets_[0]);
   currentCheckPoint = 0;
   spawnAngle = -45.0f;
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
      SpatialManager::Instance()->AddEntity(new
       Asteroid(planets_[planet_id], angle, id));
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
      SpatialManager::Instance()->AddEntity(new
       SwingAsteroid(planets_[planet_id], angle, id, clockwise != 0));
   }
}

bool Universe::PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet) {
   return planet->is_large_planet();
}

void Universe::OnEvent(const std::string& event) {
   while (!event_map_[event].empty()) {
      EventLoop::Instance()->StartNewTimer(
         this,
         event_map_[event].back().event_name,
         event_map_[event].back().delay
      );
      event_map_[event].pop_back();
   }
}

void Universe::UseLargePlanetCamera() {
   LargePlanetCamera* camera = new LargePlanetCamera(camera_->focus(),
         camera_->position(), player_->position(), player_->up(), player_->facing());
   delete camera_;
   camera_ = camera;
   player_->set_large_planet_observer(camera_);
}

void Universe::SwitchToLargePlanetGamePlay() {
   UseLargePlanetCamera();
   game_play_type_ = GAME_PLAY_TRANSITION;
}

void Universe::PlayerEntersGravityFieldOf(Planet* planet) {
   EventLoop::Instance()->PostEvent("player transitions to " + planet->id());
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

void Universe::Update() {
   camera_->Update();
   player_->Update();
   SpatialManager::Instance()->Update();

   const std::set<CollidableEntity*>& entities =
    SpatialManager::Instance()->entities();
   std::set<CollidableEntity*>::iterator start = entities.begin(),
                                         stop = entities.end();
   if (SpatialManager::Instance()->Collide(player_, start, stop) != stop) {
	if((*start)->type() == 0){
		player_->getSmallPlanetMover().set_theta(0.0);
   		PlayerEntersGravityFieldOf(planets_[currentCheckPoint]);

	}
	else{
		currentCheckPoint = dynamic_cast<CheckPoint*>(*start)->planet();
		spawnAngle = dynamic_cast<CheckPoint*>(*start)->getTheta();
	}
   }
   
   CheckPlayerChangesGravityFields();
   
   ps->update();

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
