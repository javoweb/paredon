#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "player.h"

class Controller {
 public:
  void HandleInput(std::shared_ptr<Player> player) const;

 private:
  
};

#endif