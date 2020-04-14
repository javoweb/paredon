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
    bool running();
    std::vector<SDL_Point> getBody();
    int get_score();

    // typical behaviour methods
    void play();  
    void move(Direction dir);

  private:
    int _score;
    float position;      // vector of body points

};

#endif