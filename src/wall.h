#ifndef WALL_H
#define WALL_H

#include "gameObject.h"

class Wall : public GameObject
{
  public:
    // Constructor / Destructor
    Wall(int grid_width, int grid_height);

    // Getters and setters
    void set_direction(Direction direction);

    // typical behaviour methods
    void play();  
    //void move(Direction dir);
};

#endif