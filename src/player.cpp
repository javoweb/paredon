#include "player.h"

Player::Player(int grid_width, int grid_height) : GameObject(grid_width, grid_height)
{
  _type = ObjectType::objectPlayer;
  _position = grid_width / 2;
}

std::vector<SDL_Point> Player::getBody()
{
    std::vector<SDL_Point> body;
    std::unique_lock<std::mutex> uLock(_mtx);
    for(int i = -10; i <= 10; i++)
    {
        SDL_Point point;
        point.x = static_cast<int>(_position) + i;
        point.y = _grid_height - 3;
        body.push_back(point);
    }
    return body;
}

void Player::play()
{
  // launch drive function in a thread
  threads.emplace_back(std::thread(&Player::check_hit, this));
}
  
void Player::move(Direction dir)
{
    std::unique_lock<std::mutex> uLock(_mtx, std::defer_lock);
    switch (dir)
    {
    case Direction::kLeft:
        uLock.lock();
        if(_position > 12)
        {
            _position -= 1.5;
        }
        break;
    case Direction::kRight:
        uLock.lock();
        if(_position < (_grid_width - 12))
        {
            _position += 1.5;
        }
        break;
    default:
        break;
    }

}

void Player::check_hit()
{
    std::unique_lock<std::mutex> uLock(_mtx, std::defer_lock);
}