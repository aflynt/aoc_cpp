#include "days.h"
#include "aoc_lib.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <cmath>


struct race {

  uint64_t m_dt;
  uint64_t m_dx;

  race(uint64_t dt, uint64_t dx): m_dt(dt), m_dx(dx) {}

  uint64_t cnt_wins() const {
    uint64_t n = 0;
    auto dtws = get_list_range(static_cast<uint64_t>(1), m_dt);

    for(auto& dtw: dtws){
        auto dx = dtw*m_dt-std::pow(dtw, 2);
        auto diff = dx - m_dx;
        if (diff > 0)
            ++n;
    }

    return n;
  }

};

void solve_p1(const vector<string>& lines){

  auto dt_str = split_str(lines[0], ": ")[1];
  auto dx_str = split_str(lines[1], ": ")[1];

  auto dts = split_str(dt_str, " ");
  auto dxs = split_str(dx_str, " ");

  vector<uint64_t>  vdts;
  vector<uint64_t>  vdxs;
  vector<uint64_t> ns;

  std::transform(dts.begin(), dts.end(), std::back_inserter(vdts),
                 [](std::string& s){return std::stoull(s);});

  std::transform(dxs.begin(), dxs.end(), std::back_inserter(vdxs),
                 [](std::string& s){return std::stoull(s);});

  for (uint64_t i = 0ull; i < vdts.size(); ++i)
      ns.emplace_back(race(vdts[i],vdxs[i]).cnt_wins());

  uint64_t product = std::accumulate(ns.begin(), ns.end(),
                                     1ull, std::multiplies<uint64_t>());

  std::cout << "p1: " << product << "\n";
}


template <typename T>
void quadratic(T a, T b, T c, T& xlo, T& xhi){

  auto x1 = (-b + std::sqrt(b*b - 4*a*c)) / (2*a);
  auto x2 = (-b - std::sqrt(b*b - 4*a*c)) / (2*a);
  xhi = std::max(x1,x2);
  xlo = std::min(x1,x2);
}

void solve_p2(const vector<string>& lines){

  auto dt_str = split_str(lines[0], ": ")[1];
  auto dx_str = split_str(lines[1], ": ")[1];

  rm_whitespace(dt_str);
  rm_whitespace(dx_str);

  double dt = std::stod(dt_str);
  double dx = std::stod(dx_str);
  double a = 1;
  double b = -dt;
  double c = dx;
  double xlo = 0.0;
  double xhi = 0.0;

  quadratic(a, b, c, xlo, xhi);

  xhi = std::floor(xhi);
  xlo = std::ceil(xlo);
  int64_t cnt = static_cast<int64_t>( xhi - xlo + 1);

  std::cout << "p2: " << cnt << std::endl;
}




void solve_day06(const std::string &fname)
{
  using std::vector;
  using std::string;

  auto lines = get_lines(fname);
  solve_p1(lines);
  solve_p2(lines);


}
