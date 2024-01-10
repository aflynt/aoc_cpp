#include "day02.h"
#include "game.h"

auto get_lines_d2(const std::string& fname) -> std::vector<std::string> {

  std::vector<std::string> lines;
  std::string line;
  std::ifstream istrm(fname, std::ios::in);

  if (istrm.is_open()){
      while (std::getline(istrm, line)){ lines.push_back(line); }
  }
  return lines;
}

std::vector<std::string> split_str(std::string s, const std::string& delimiter){
  std::vector<std::string> vs;

  size_t pos = 0;
  while ((pos = s.find(delimiter)) != std::string::npos){
      std::string token = s.substr(0, pos);
      vs.push_back(token);
      s.erase(0, pos+delimiter.length());
  }
  std::string token = s;
  vs.push_back(token);

  return vs;
}

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
  auto lines = get_lines_d2(fname);

  solve_day02_part1(lines);
  solve_day02_part2(lines);

}
