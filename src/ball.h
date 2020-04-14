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
  SDL_Point get_point();
  void get_position(float &pos_x, float &pos_y);

  //typical behaviour methods
  void play() override;
  void increase_speed();
  
 private:
  //typical behaviour methods
  void update_position();
  void norm_direction();

  float _pos_x;
  float _pos_y;
  float _dir_x;
  float _dir_y;
  float _speed{0.008f};
  
};

#endif