#ifndef AOC_LIB_H
#define AOC_LIB_H

#include <functional>
#include <locale>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <iostream>

using std::string;
using std::vector;
using std::set;
using std::ostream;

auto get_lines(const string& fname) -> vector<string>;

auto char_in_set(char c, const set<char> cs) -> bool;

auto split_str(string s, const string& delimiter) -> vector<string>;

//auto get_list_range(int fm, int to) -> vector<int>;
template <typename T>
vector<T> get_list_range(T fm, T to){
  T n = to - fm;
  vector<T> lr(n);
  std::iota(lr.begin(), lr.end(), fm);

  return lr;
}



template<typename T>
auto print_vec(const std::vector<T>& vs, char sep='\n', std::ostream& os=std::cout) -> std::ostream& {
  for (const auto& v : vs) {
      os << v << sep;
  }
  return os;
}

template<typename T> void rm_whitespace(T& s){
  s.erase(std::remove_if(s.begin(),
                         s.end(),
                         [](unsigned char c) { return std::isspace(c); }),
      s.end());
}

#endif // AOC_LIB_H
