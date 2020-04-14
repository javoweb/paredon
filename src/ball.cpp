#include "ball.h"
#include <iostream>
#include <random>
#include <mutex>
#include <cmath>

Ball::Ball(int grid_width, int grid_height) : GameObject(grid_width, grid_height)
{
  _type = ObjectType::objectBall;
  _pos_x = grid_width / 2;
  _pos_y = _grid_height / 2;
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<int> distr(-10, 10);
  _dir_x = distr(eng);
  _dir_y = distr(eng);
  norm_direction();
}

void Ball::norm_direction()
{
  float correction_factor = 20.0 / std::sqrt(std::pow(_dir_x, 2) + std::pow(_dir_y, 2));
  _dir_y *= correction_factor;
  _dir_x *= correction_factor;
}

void Ball::set_direction(float dir_x, float dir_y)
{
  std::unique_lock<std::mutex> uLock(_mtx);
  _dir_x = dir_x;
  _dir_y = dir_y;
  norm_direction();
}

void Ball::get_direction(float &dir_x, float &dir_y)
{
  std::unique_lock<std::mutex> uLock(_mtx);
  dir_x = _dir_x;
  dir_y = _dir_y;
}

SDL_Point Ball::get_point()
{
  std::unique_lock<std::mutex> uLock(_mtx);
  SDL_Point point;
  point.x = _pos_x;
  point.y = _pos_y;
  return point;
}

void Ball::get_position(float &pos_x, float &pos_y)
{
  std::unique_lock<std::mutex> uLock(_mtx);
  pos_x = _pos_x;
  pos_y = _pos_y;
}

void Ball::play(){
  // launch drive function in a thread
  threads.emplace_back(std::thread(&Ball::update_position, this));
}

void Ball::increase_speed()
{
  // launch drive function in a thread
  std::unique_lock<std::mutex> uLock(_mtx);
  _speed += 0.0001;
}

void Ball::update_position()
{
  std::unique_lock<std::mutex> uLock(_mtx, std::defer_lock);
  // Initialize variables
  int cycleDuration = 5;  // Duration between cycles in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  lastUpdate = std::chrono::system_clock::now();

  // Infinite loop
  while (!_game_over) {
    // Sleep for 1ms in order to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // Compute time since last phase update
    long timeSinceLastUpdate =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - lastUpdate)
            .count();
    if (timeSinceLastUpdate >= cycleDuration) {
      // Toggle _currentPhase state
      uLock.lock();
      _pos_x += _dir_x * _speed;
      _pos_y += _dir_y * _speed;
      if (_pos_y >= _grid_height)
      {
        stop();
      }
      uLock.unlock();
      // Reset stop whatch
      lastUpdate = std::chrono::system_clock::now();
    }
  }
}