#ifndef BALL_H
#define BALL_H

#include <vector>
#include "SDL.h"
#include "gameObject.h"

class Ball : public GameObject
{

 public:
  // constructor / destructor
  Ball(int grid_width, int grid_height);

  // getter and setter
  void set_direction(float dir_x, float dir_y);
  void get_direction(float &dir_x, float &dir_y);
  SDL_Point get_position();

  //typical behaviour methods
  void play();
  
 private:
  //typical behaviour methods
  void update_position();
  void norm_direction();

  float pos_x;
  float pos_y;
  float dir_x;
  float dir_y;
  float speed{0.1f};
  
};

#endif