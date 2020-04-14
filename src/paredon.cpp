#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

void log_score(long score , std::string name){
  std::ofstream outfile;
  std::string data = std::to_string(score) + " " + name;
  outfile.open("../game_log.txt", std::ofstream::out | std::ofstream::app);
  outfile << data;
}

bool check_high_score(long score){
  std::string line;
  std::string data;
  std::ifstream infile("../game_log.txt");
  if (infile.is_open()){
    while(std::getline(infile, line)){
      std::istringstream linestream(line);
      linestream >> data;
      if (std::stol(data) > score){
        return false;
      }
    }
  }
  return true;
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{800 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{128};
  constexpr std::size_t kGridHeight{160};

  // Ask for player name
  std::string player_name;
  std::cout << "Set Player's name: ";
  std::cin >> player_name;
  std::cout << "Hello " << player_name << std::endl << "Starting game..." << std::endl;

  // Game Start
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  long score = game.GetScore();
  std::cout << "Game has terminated successfully!\n";
  if (check_high_score(score)){
    std::cout << "Congratulations!! New High Score" << std::endl;
  }
  std::cout << "Score: " << score << "\n";
  log_score(score, player_name);
  return 0;
}