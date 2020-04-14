#include "game.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height) : _ball(grid_width, grid_height)
{
  _player = std::make_shared<Player>(grid_width, grid_height);

  // Initialize Walls
  _walls.emplace_back(Wall(grid_width, grid_height));
  _walls.back().set_direction(Wall::Direction::kUp);
  _walls.emplace_back(Wall(grid_width, grid_height));
  _walls.back().set_direction(Wall::Direction::kLeft);
  _walls.emplace_back(Wall(grid_width, grid_height));
  _walls.back().set_direction(Wall::Direction::kRight);

  // Draw wall points
  // Up wall
  for(int i=0; i<grid_width; i++)
  {
    SDL_Point point;
    point.x = i;
    point.y = 0;
    _wall_points.push_back(point);
  }

  // Left wall
  for(int i=0; i<grid_height; i++)
  {
    SDL_Point point;
    point.x = 0;
    point.y = i;
    _wall_points.push_back(point);
  }

  // Right wall
  for(int i=0; i<grid_width; i++)
  {
    SDL_Point point;
    point.x = i;
    point.y = grid_width - 1;
    _wall_points.push_back(point);
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  _player->play();
  _ball.play();
  std::for_each(_walls.begin(), _walls.end(), [](Wall &it){it.play();});

  while (_player->running()) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(_player);
    std::vector<SDL_Point> player_points = _player->getBody();
    renderer.Render(player_points, _wall_points, _ball.get_position());

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score++ , frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
