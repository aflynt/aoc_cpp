#include "days.h"
#include "aoc_lib.h"
#include "game.h"

#include <vector>
#include <string>
#include <iostream>


void solve_day02_part1(std::vector<std::string>& lines){
  int ans = 0;
  for(auto& line : lines){
      auto g = Game(line);
      ans += g.get_res();
  }
  std::cout << "ans: " << ans << "\n";
}

void solve_day02_part2(std::vector<std::string>& lines){
  int ans = 0;
  for(auto& line : lines){
      auto g = Game(line);
      ans += g.get_pwr();
  }
  std::cout << "ans: " << ans << "\n";
}

void solve_day02(const std::string& fname){
  auto lines = get_lines(fname);

  solve_day02_part1(lines);
  solve_day02_part2(lines);

}
