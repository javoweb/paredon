#include "wall.h"

Wall::Wall(int grid_width, int grid_height) : GameObject(grid_width, grid_height)
{
  _type = ObjectType::objectWall;
}

void Wall::set_direction(Direction direction)
{
    _direction = direction;
}

void Wall::play()
{
    // launch drive function in a thread
    threads.emplace_back(std::thread(&Wall::check_hit, this));
}

void Wall::check_hit()
{
    std::unique_lock<std::mutex> uLock(_mtx, std::defer_lock);
}