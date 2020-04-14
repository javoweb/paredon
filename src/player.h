#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "gameObject.h"
#include "ball.h"

class Player : public GameObject
{
  public:
    // Constructor / Destructor
    Player(int grid_width, int grid_height);

    // Getters and setters
    std::vector<SDL_Point> getBody();
    int get_score();

    // typical behaviour methods
    void play(std::shared_ptr<Ball> ball);  
    void move(Direction dir);
    

  private:
    void check_hit(std::shared_ptr<Ball> ball);
    float _position;      // vector of body points

};

#endif