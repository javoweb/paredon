#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "ball.h"
#include "player.h"
#include "wall.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  long GetScore() const { return _score; }

 private:
  std::shared_ptr<Ball> _ball;
  std::shared_ptr<Player> _player;
  Wall _upWall;
  Wall _leftWall;
  Wall _rightWall;
  std::vector<SDL_Point> _wall_points;
  long _score{0};
};

#endif