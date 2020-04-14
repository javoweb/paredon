#include "wall.h"
#include <cmath>

Wall::Wall(int grid_width, int grid_height) : GameObject(grid_width, grid_height)
{
  _type = ObjectType::objectWall;
}

void Wall::set_direction(Direction direction)
{
    _direction = direction;
}

void Wall::play(std::shared_ptr<Ball> ball)
{
    // launch drive function in a thread
    threads.emplace_back(std::thread(&Wall::check_hit, this, ball));
}

void Wall::check_hit(std::shared_ptr<Ball> ball)
{
    // Initialize variables
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
        // Check if ball touched the wall and update ball direction
        float pos_x;
        float pos_y;
        ball->get_position(pos_x, pos_y);
        switch (_direction)
        {
        case Direction::kUp:
            if (pos_y < 2)
            {
                float dir_x;
                float dir_y;
                ball->get_direction(dir_x, dir_y);
                ball->set_direction(dir_x, std::abs(dir_y));
            }
            break;
        case Direction::kLeft:
            if (pos_x < 2)
            {
                float dir_x;
                float dir_y;
                ball->get_direction(dir_x, dir_y);
                ball->set_direction(std::abs(dir_x), dir_y);
            }
            break;
        case Direction::kRight:
            if (pos_x > (_grid_width - 2))
            {
                float dir_x;
                float dir_y;
                ball->get_direction(dir_x, dir_y);
                ball->set_direction(-std::abs(dir_x), dir_y);
            }
            break;
        default:
            break;
        }
        // Reset stop whatch
        lastUpdate = std::chrono::system_clock::now();
        }
    }
}