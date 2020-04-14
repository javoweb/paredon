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
  long Game::GetScore() const { return _score; }

 private:
  Ball _ball;
  std::shared_ptr<Player> _player;
  std::vector<Wall> _walls;
  std::vector<SDL_Point> _wall_points;
  long _score{0};
};

#endif