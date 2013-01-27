#ifndef _UNIVERSE_H_
#define _UNIVERSE_H_

#include "../core/game.h"
#include "../core/timer.h"
#include "planet.h"

class Asteroid;
class SwingAsteroid;
class RootNode;
class Camera;
class Player;

enum GamePlayType { GAME_PLAY_SMALL, GAME_PLAY_LARGE };
class Universe : public Game,
                 public Timer::Delegate {
  public:
   Universe();

   virtual void Update();
   virtual void Draw();

   // Input handling //
   virtual void OnLeftButtonDown();
   virtual void OnLeftButtonUp();

   virtual void OnRightButtonDown();
   virtual void OnRightButtonUp();

   virtual void OnDownButtonDown();
   virtual void OnDownButtonUp();

   virtual void OnUpButtonDown();
   virtual void OnUpButtonUp();

   virtual void OnJumpButtonDown();
   virtual void OnJumpButtonUp();

   virtual void OnCameraUpDown();
   virtual void OnCameraDownDown();
   // Input handling //

   virtual void OnExpiration(const std::string& event_name);

  private:
   void LoadInPlanets();
   void PlayerEntersGravityFieldOf(Planet* planet);
   bool PlayerTransitionsFromSmallPlanetToLargePlanet(Planet* planet);
   void SwitchToLargePlanetGamePlay();
   template <class T>
   void UpdateAsteroids(std::vector<T>& asteroids);

   bool is_small_planet_gameplay() const
    { return game_play_type_ == GAME_PLAY_SMALL; }
   bool is_large_planet_gameplay() const
    { return game_play_type_ == GAME_PLAY_LARGE; }

   void CheckPlayerChangesGravityFields();
   void OnMovementButtonUp();
   void UseLargePlanetCamera();

   Camera* camera_;
   GamePlayType game_play_type_;
   std::vector<Planet*> planets_;
   std::vector<Asteroid*> asteroids_;
   std::vector<SwingAsteroid*> swing_asteroids_;
   Player* player_;
};

#endif
