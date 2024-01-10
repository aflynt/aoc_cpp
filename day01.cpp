#include "day01.h"


auto get_lines(const std::string& fname) -> std::vector<std::string> {

  std::vector<std::string> lines;
  std::string line;
  std::ifstream istrm(fname, std::ios::in);

  if (istrm.is_open()){
      while (std::getline(istrm, line)){ lines.push_back(line); }
  }
  return lines;
}

auto get_line_result(const std::string& line, const std::vector<std::string>& good_chars) -> unsigned long {

  std::map<std::string, std::string> name2val{{"one"  , "1"},{"two"  , "2"},{"three", "3"},{"four" , "4"},{"five" , "5"},{"six"  , "6"},{"seven", "7"},{"eight", "8"},{"nine" , "9"},{"1", "1"},{"2", "2"},{"3", "3"},{"4", "4"},{"5", "5"},{"6", "6"},{"7", "7"},{"8", "8"},{"9", "9"}};
  std::vector<std::tuple<unsigned long, std::string>> nums;

  for (auto i = 0ul; i < line.length(); ++i){
      for (auto gc : good_chars){
          auto n = line.find(gc, i);
          if (n != std::string::npos){
              nums.push_back({i+n, gc});
          }
      }
  }

  std::sort(nums.begin(), nums.end());
  nums.erase(std::unique(nums.begin(), nums.end()), nums.end());

  auto n1 = std::get<1>(nums.front());
  auto n2 = std::get<1>(nums.back());
  auto c1 = name2val[n1].c_str()[0];
  auto c2 = name2val[n2].c_str()[0];
  int in1 = 10*((int)c1 - '0');
  int in2 =  1*((int)c2 - '0');

  return in1+in2;
}

auto get_line_results(const std::vector<std::string>& lines, const std::vector<std::string>& good_chars) -> unsigned long {

  unsigned long ans = 0;
  for (const auto& line: lines)
      ans += get_line_result(line, good_chars);

  return ans;
}

void solve_day01(const std::string& fname){
  auto lines = get_lines(fname);

  std::vector<std::string> goodchars1 = {"0","1","2","3","4","5","6","7","8","9"};
  std::vector<std::string> goodchars2 = {"0","1","2","3","4","5","6","7","8","9","one","two","three","four","five","six","seven","eight","nine"};

  std::cout << "sum: " << get_line_results(lines, goodchars1) << "\n";
  std::cout << "sum: " << get_line_results(lines, goodchars2) << "\n";
}
