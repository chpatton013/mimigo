#include "universe.h"
#include "sdl/sdl_event_loop.h"
#include "asteroid.h"
#include "swing_asteroid.h"
#include "player.h"
#include "scene_hierarchy/root_node.h"
#include "scene_hierarchy/entity_component_node.h"
#include "small_planet_camera.h"
#include "large_planet_camera.h"
#include "checkpoint.h"
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <utility>
#include <iterator>


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
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/asteroid.obj", "textures/purple.bmp");
   EntityComponent* fish = LoadEntityComponentFromOBJ("meshes/puffer_fish.obj", "textures/earth.bmp");
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

void ParseCheckPointsFile(std::vector<Planet*> planets) {
   std::ifstream in("checkpoints.lvl");

	std::string id;
         std::string planet_id;
         float angle;
std::string full_id;


   std::string line;
   EntityComponent* flag = LoadEntityComponentFromOBJ("meshes/flag.obj", "textures/edgar.bmp");
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else {
         stream >> id;
         stream >> planet_id;
         stream >> angle;

         full_id = "checkpoint" + id;

            SceneNode::Get("planet" + planet_id)->AddChild(new
             EntityComponentNode(full_id, flag));

        SceneNode::Get(full_id)->set_visible(true);

	int planetID = atoi(planet_id.c_str());
	planetID--;

SpatialManager::Instance()->AddEntity(new CheckPoint(planets[planetID], planetID,  angle, full_id));
      }
   }
}

void Universe::ParseAssetsFile() {
   std::ifstream in("assets.txt");

	std::string name;
         std::string planet_id;
         float xAngle;
	float zAngle;
std::string full_id;


   std::string line;

   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else {
         stream >> name;
         stream >> planet_id;
         stream >> xAngle;
	stream >> zAngle;

	int num = entity_num_.find(name)->second;

std::ostringstream convert;
convert << num;
full_id = name + convert.str();

entity_num_[name] = num + 1;
            SceneNode::Get("planet" + planet_id)->AddChild(new
             EntityComponentNode(full_id, entity_data_.find(name)->second));

        SceneNode::Get(full_id)->set_visible(true);
      }
   }
}

void Universe::ParseEntityFile() {
   std::ifstream in("entities.txt");

	std::string name;
	std::string mesh_location;
	std::string texture_location;


   std::string line;
   while (getline(in, line)) {
      std::istringstream stream(line);
      if (line.empty() || line[0] == '#') {
      }
      else {
	stream >> name;
	stream >> mesh_location;
	stream >> texture_location;

	entity_data_[name] = LoadEntityComponentFromOBJ("meshes/" + mesh_location, "textures/" + texture_location);
	entity_num_[name] = 0;
      }
   }
}

void ParsePlanetFile(const std::string& filename, std::vector<Planet*> *planets) {
   std::ifstream in(filename.c_str());

   PlanetType planet_type = PLANET_TYPE_SMALL;

   std::string line;
   EntityComponent* sphere = LoadEntityComponentFromOBJ("meshes/sphere.obj", "textures/grass.bmp");
   EntityComponent* tree = LoadEntityComponentFromOBJ("meshes/tree.obj", "textures/earth.bmp");
   EntityComponent* shark = LoadEntityComponentFromOBJ("meshes/shark.obj", "textures/purple.bmp");
   EntityComponent* adobe = LoadEntityComponentFromOBJ("meshes/adobe_house.obj", "textures/earth.bmp");
   EntityComponent* house = LoadEntityComponentFromOBJ("meshes/tree_house.obj", "textures/earth.bmp");
   EntityComponent* cactus = LoadEntityComponentFromOBJ("meshes/cactus.obj", "textures/earth.bmp");
   EntityComponent* flower = LoadEntityComponentFromOBJ("meshes/flower.obj", "textures/earth.bmp");
   EntityComponent* coral = LoadEntityComponentFromOBJ("meshes/coral.obj", "textures/earth1.bmp");
   EntityComponent* asteroid = LoadEntityComponentFromOBJ("meshes/asteroid.obj", "textures/earth.bmp");

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
   EntityComponent* shark = LoadEntityComponentFromOBJ("meshes/shark.obj", "textures/dots.bmp");
   EntityComponent* fish = LoadEntityComponentFromOBJ("meshes/puffer_fish.obj", "textures/sand.bmp");
   EntityComponent* gopher = LoadEntityComponentFromOBJ("meshes/go_gopher.obj", "textures/edgar.bmp");
   EntityComponent* flag = LoadEntityComponentFromOBJ("meshes/flag.obj", "textures/earth1.bmp");
   

   ParsePlanetFile("planets.lvl", &planets_);
   
   RootNode::Instance()->AddChild(new EntityComponentNode("shark1", shark));
   assets_.push_back(new Assets("shark", "1", glm::vec3(0, 0.8, 0), glm::vec3(5.0, 5.0, 5.0), glm::vec3(1.0, 1.0, 1.0), 0.0, planets_[2]));
   
   RootNode::Instance()->AddChild(new EntityComponentNode("fish2", fish));
   assets_.push_back(new Assets("fish", "2", glm::vec3(0, 0.8, 0), glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), 0.0, planets_[2]));
   
   RootNode::Instance()->AddChild(new EntityComponentNode("fish3", fish));
   assets_.push_back(new Assets("fish", "3", glm::vec3(-0.8, 0, 0), glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), 0.0, planets_[2]));
   
   RootNode::Instance()->AddChild(new EntityComponentNode("gopher4", gopher));
   assets_.push_back(new Assets("gopher", "4", glm::vec3(.1, 0.5, 0), glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), 0.0, planets_[3]));   
   
   RootNode::Instance()->AddChild(new EntityComponentNode("gopher5", gopher));
   assets_.push_back(new Assets("gopher", "5", glm::vec3(-.1, -0.5, 0), glm::vec3(.5,.5,.5), glm::vec3(1.0, 1.0, 1.0), 0.0, planets_[3]));
}

Universe::Universe() :
   game_play_type_(GAME_PLAY_SMALL)
{
   camera_ = new SmallPlanetCamera();
   ParseEntityFile();
   LoadInPlanets();
   ParseAssetsFile();
   ParseAsteroidFile();
   ParseCheckPointsFile(planets_);
   player_ = new Player(planets_[0], camera_);

   glm::vec3 min, max;
   GetBounds(&min, &max);
   SpatialManager::Instance()->Establish(min, max);

   ps = new ParticleSystem(15);
   light_ = new DirectionLight(glm::vec3(0.4f, 0.4f, 0.4f),
                               glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
                               glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

   currentCheckpoint = 0;
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

	std::set<CollidableEntity*> collidedEntities = SpatialManager::Instance()->Collide(player_);

   if (!collidedEntities.empty()) {
	for (std::set<CollidableEntity*>::iterator it = collidedEntities.begin(); it != collidedEntities.end(); ++it) {
		if((*it)->type() == 0){
  			PlayerEntersGravityFieldOf(planets_[currentCheckpoint]);
			break;
		}
		else if((*it)->type() == 1){
  			currentCheckpoint = dynamic_cast<CheckPoint*>(*it)->planet();
			break;
		}
	}
	
   }

   CheckPlayerChangesGravityFields();

   ps->update();
   assets_[0]->Bounce();
   assets_[1]->BackAndForth(0, 90, 5.0);
   assets_[2]->BackAndForth(200, 270, 5.0);
   assets_[3]->UpAndDown(.5, 0.0, .1, .05);
   assets_[4]->UpAndDown(.5, 0.0, .1, .05);
   
   planets_[4]->Pogo();
   planets_[5]->Gopo();

}

void Universe::Draw() {
   camera_->SetView();
   light_->Draw();
   RootNode::Instance()->Draw();
   RootNode::Instance()->PrintTree();
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

void Universe::GetBounds(glm::vec3* min, glm::vec3* max) {
   glm::vec3 running_min(FLT_MAX), running_max(FLT_MIN);

   for (std::vector<Planet*>::iterator itr = planets_.begin();
         itr != planets_.end(); ++itr) {
      glm::vec3 current_min = (*itr)->bounding_region()->min();
      glm::vec3 current_max = (*itr)->bounding_region()->max();

      running_min.x = std::min(running_min.x, current_min.x);
      running_min.y = std::min(running_min.y, current_min.y);
      running_min.z = std::min(running_min.z, current_min.z);

      running_max.x = std::max(running_max.x, current_max.x);
      running_max.y = std::max(running_max.y, current_max.y);
      running_max.z = std::max(running_max.z, current_max.z);
   }

   *min = running_min;
   *max = running_max;
}
