#include "game.h"
#include "day02.h"
#include <algorithm>

Game::Game(std::string game_str)
{
  // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
  auto lr = split_str(game_str, ": ");
  auto leader = lr[0];
  game_str = lr[1];
  auto g_id = split_str(leader, " ");
  auto id_str = g_id[1];
  ID = std::stoi(id_str);

  std::vector<std::string> game_sets = split_str(game_str, "; ");

  std::vector<std::tuple<int, int, int>> set_picks;
  int mr = 0;
  int mg = 0;
  int mb = 0;

  for (auto& setstr: game_sets){
      // 3 blue, 4 red
      std::vector<std::string> pick_list = split_str(setstr, ", ");
      int pick_r = 0;
      int pick_g = 0;
      int pick_b = 0;
      for (auto& pick : pick_list){
          std::vector<std::string> LR = split_str(pick," ");
          auto cnt_str = LR[0];
          auto cube_type = LR[1];
          int cnt = std::stoi(cnt_str);
          if (cube_type.compare("red") == 0){
              pick_r = cnt;
              if (pick_r > MAX_R) possible = false;
              mr = std::max(mr, pick_r);
          }
          else if (cube_type.compare("green") == 0){
              pick_g = cnt;
              if (pick_g > MAX_G) possible = false;
              mg = std::max(mg, pick_g);
          }
          else{
              pick_b = cnt;
              if (pick_b > MAX_B) possible = false;
              mb = std::max(mb, pick_b);
          }
      }
      set_picks.push_back({pick_r, pick_g, pick_b});
  }
  if (possible)
      res = ID;
  power = mr * mg * mb;
}
