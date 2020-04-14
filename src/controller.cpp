#include <iostream>
#include "SDL.h"
#include "controller.h"
#include "player.h"



void Controller::HandleInput(std::shared_ptr<Player> player) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      player->stop();
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          player->move(Player::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          player->move(Player::Direction::kRight);
          break;
      }
    }
  }
}