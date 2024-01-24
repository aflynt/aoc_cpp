#include "aoc_lib.h"
#include "days.h"
#include "card.h"

#include <fstream>
#include <iostream>
#include <map>


void solve_p1(const std::string& fname){
  auto lines = get_lines(fname);

  long long ans = 0;
  for (auto& line: lines)
      ans += card(line).get_v();

  std::cout << ans << "\n";
}

auto make_map(std::vector<card>& cards) -> std::map<int,int> {

  std::map<int,int> cmap;

  for (auto& card: cards){
      auto id = card.get_id();
      auto n = card.get_n();
      cmap[id] = n;
  }

  return cmap;
}


long long get_card_scratchers(int id, int num_wins, long long ns, const std::map<int,int>& cmap){

    ++ns;

    if (num_wins){
       ++id;
        auto lr = get_list_range(id, id+num_wins);
        for (int iid: lr){
            ns = get_card_scratchers(iid, cmap.at(iid), ns, cmap);
        }
    }

    return ns;
}


void solve_p2(const std::string& fname){
  auto lines = get_lines(fname);

  std::vector<card> vc;
  for (auto& line: lines){
      vc.emplace_back(card(line));
  }

  auto cmap = make_map(vc); //  map[id] -> num_wins

  long long ns = 0;
  // for id,num_wins in map:
  for (auto& [id, num_wins] : cmap){
      if (num_wins) {
          ns = get_card_scratchers(id, num_wins, ns, cmap);
      } else {
          ++ns;
      }
  }

  std::cout << ns << std::endl;

}

void solve_day04(const std::string &fname) {

  solve_p1(fname);
  solve_p2(fname);

}
