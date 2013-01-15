#include "planet_rotater.h"

#include <iostream>

inline
float clockwise_acceleration(float acceleration) {
   return std::abs(acceleration);
}

inline
float counter_clockwise_acceleration(float acceleration) {
   return -std::abs(acceleration);
}

void PlanetRotater::StartRotatingClockwise(float move_speed,
                                           float acceleration) {
   acceleration_ = clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(
      move_speed, acceleration_);
}

void PlanetRotater::StartRotatingCounterClockwise(float move_speed,
                                                  float acceleration) {
   acceleration_ = counter_clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(
      move_speed, acceleration_);
}

void PlanetRotater::StopRotating(float acceleration) {
   if (is_moving_clockwise())
      acceleration_ = counter_clockwise_acceleration(acceleration);
   else
      acceleration_ = clockwise_acceleration(acceleration);
   acceleration_frames_ = CalculateFramesUntilMoveSpeed(0.0f, acceleration_);
}

void PlanetRotater::Update() {
   if (acceleration_frames_ > 0) {
      move_speed_ += acceleration_;
      --acceleration_frames_;
   }
   std::cout << move_speed_ << std::endl;
}
