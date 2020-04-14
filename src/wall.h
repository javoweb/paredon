#ifndef WALL_H
#define WALL_H

#include "gameObject.h"
#include "ball.h"

class Wall : public GameObject
{
  public:
    // Constructor / Destructor
    Wall(int grid_width, int grid_height);

    // Getters and setters
    void set_direction(Direction direction);

    // typical behaviour methods
    void play(std::shared_ptr<Ball> ball);  
    //void move(Direction dir);

  private:
    void check_hit(std::shared_ptr<Ball> ball);
    Direction _direction;
};

#endif