#include "player.h"
#include <cmath>

Player::Player(int grid_width, int grid_height) : GameObject(grid_width, grid_height)
{
  _type = ObjectType::objectPlayer;
  // Sets Player platform in the middle
  _position = grid_width / 2;
}

std::vector<SDL_Point> Player::getBody()
{
    std::vector<SDL_Point> body;
    std::unique_lock<std::mutex> uLock(_mtx);
    // Generate points for every part of the player platform
    for(int i = -10; i <= 10; i++)
    {
        SDL_Point point;
        point.x = static_cast<int>(_position) + i;
        point.y = _grid_height - 3;
        body.push_back(point);
    }
    return body;
}

void Player::play(std::shared_ptr<Ball> ball)
{
  // launch drive function in a thread
  threads.emplace_back(std::thread(&Player::check_hit, this, ball));
}
  
void Player::move(Direction dir)
{
    std::unique_lock<std::mutex> uLock(_mtx, std::defer_lock);
    // Set new platform position in function of the direction key pressed
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

void Player::check_hit(std::shared_ptr<Ball> ball)
{
    int cycleDuration = 10;  // Duration between cycles in ms
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
        // Check if ball touched platform and update new ball direction
        float pos_x;
        float pos_y;
        ball->get_position(pos_x, pos_y);
        if (pos_y > (_grid_height - 3) && std::abs(pos_x - _position) < 10)
        {
            float dir_x;
            float dir_y;
            ball->get_direction(dir_x, dir_y);
            ball->set_direction(dir_x + pos_x - _position, -std::abs(dir_y));
        }
        // Reset stop whatch
        lastUpdate = std::chrono::system_clock::now();
        }
    }
}