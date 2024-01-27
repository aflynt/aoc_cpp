#include "aoc_lib.h"
#include "gridpos.h"
#include "days.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>

using std::vector;
using std::string;
using std::map;

class History {

public:
  explicit History(const string& line, bool reverse=false) {

      auto vstrs = split_str(line, " ");
      if (reverse)
          std::transform(vstrs.rbegin(), vstrs.rend(), std::back_inserter(m_hvals), [](string& s){return std::stoll(s); });
      else
          std::transform(vstrs.begin(), vstrs.end(), std::back_inserter(m_hvals), [](string& s){return std::stoll(s); });

      extrapolate();
  }

  int64_t get_last_val() const { return m_hvals.back(); }
  const vector<int64_t>& get_history() const { return m_hvals; }

private:
  void extrapolate();

  vector<int64_t> m_hvals;

};


vector<int64_t> get_diffs(vector<int64_t> hvals){

  std::vector<int64_t> diffs;
  std::adjacent_difference(hvals.begin(), hvals.end(), std::back_inserter(diffs));

  diffs.erase(diffs.begin());

  return diffs;
}

void History::extrapolate(){
  // extrapolate this history

  vector<int64_t> diffs = get_diffs(m_hvals);
  bool all_zero = std::all_of(diffs.cbegin(), diffs.cend(), [](auto v){ return v == 0;});

  vector<vector<int64_t>> h_lists;
  h_lists.push_back(m_hvals);
  h_lists.push_back(diffs);

  while (!all_zero) {
      diffs = get_diffs(diffs);
      h_lists.push_back(diffs);
      all_zero = std::all_of(diffs.cbegin(), diffs.cend(), [](auto v){ return v == 0;});
  }

  for (auto& h_list : h_lists)
    h_list.push_back(0);

  // second to last row
  auto ri = h_lists.rbegin()+1;

  for(int i=0; ri != h_lists.rend(); ++ri, ++i){
      auto& h_list = *ri;

      auto  val_left = *(h_list.rbegin()+1);
      auto& row_down = *(ri-1);
      auto  val_down = row_down.back();

      auto& h_list_end = h_list.back();
      h_list_end = val_left + val_down;

  }

  m_hvals.push_back(h_lists[0].back());

}

void solve_day09(const std::string& fname){

    auto lines = get_lines(fname);

    int64_t ans_0 = 0;
    int64_t ans_1 = 0;

    for (auto& line : lines){
        ans_0 += History(line, false).get_last_val();
        ans_1 += History(line, true).get_last_val();
    }

    std::cout << ans_0 << std::endl;
    std::cout << ans_1 << std::endl;
}



