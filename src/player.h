#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "SDL.h"
#include "gameObject.h"

class Player : public GameObject
{
  public:
    // Constructor / Destructor
    Player(int grid_width, int grid_height);

    // Getters and setters
    std::vector<SDL_Point> getBody();
    int get_score();

    // typical behaviour methods
    void play();  
    void move(Direction dir);
    

  private:
    void check_hit();
    float _position;      // vector of body points

};

#endif