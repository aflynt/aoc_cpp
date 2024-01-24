#include "aoc_lib.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <algorithm>


auto get_lines(const std::string& fname) -> std::vector<std::string> {

  std::vector<std::string> lines;
  std::string line;
  std::ifstream istrm(fname, std::ios::in);

  if (istrm.is_open()){
      while (std::getline(istrm, line)){ lines.push_back(line); }
  }
  return lines;
}

bool char_in_set(char c, const std::set<char> cs){

    if (auto search = cs.find(c); search != cs.end())
      return true;
    return false;
}

auto  split_str(std::string s, const std::string& delimiter) -> std::vector<std::string> {
  std::vector<std::string> vs;

  size_t pos = 0;
  while ((pos = s.find(delimiter)) != std::string::npos){
      std::string token = s.substr(0, pos);
      vs.push_back(token);
      s.erase(0, pos+delimiter.length());
  }
  std::string token = s;
  vs.push_back(token);

  auto it = std::remove(vs.begin(), vs.end(), std::string(""));
  vs.erase(it, vs.end());

  return vs;
}

//vector<int> get_list_range(int fm, int to){
//  int n = to - fm;
//  vector<int> lr(n);
//  std::iota(lr.begin(), lr.end(), fm);
//
//  return lr;
//}
