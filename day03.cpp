#include "days.h"
#include "aoc_lib.h"
#include "gridpos.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <numeric>
#include <iomanip>
#include <map>


std::set<char> numchars = {'0','1','2','3','4','5','6','7','8','9'};
std::set<char> non_gear_chars = {'.','0','1','2','3','4','5','6','7','8','9'};

auto get_nums(const std::vector<std::string>& lines) -> std::vector<Gridpos> {

  std::vector<Gridpos> nums;

  for (auto r = 0ul; r < lines.size(); ++r){
      bool innum = false;
      std::vector<char> numlist;
      auto row = r;
      auto col = 0ul;
      auto line = lines[r];
      for (auto c = 0ul; c < line.length(); ++c){
          char char_ = line[c];
          if (char_in_set(char_, numchars)){
              numlist.push_back(char_);
              if (!innum) {
                  innum = true;
                  row = r;
                  col = c;
              }
          } else if (innum) {
              std::string numstr(numlist.begin(), numlist.end());
              int num = std::stoi(numstr);
              nums.emplace_back(Gridpos(row, col, num));
              numlist.clear();
              innum = false;
          }
      }
  }
  return nums;
}

std::vector<Gridpos> get_all_gears(const std::vector<std::string>& lines){
  std::vector<Gridpos> gears;

  for (auto r = 0ul; r < lines.size(); ++r){
      auto line = lines[r];
      for (auto c = 0ul; c < line.length(); ++c){
          char char_ = line[c];
          if (!char_in_set(char_, non_gear_chars)) {
          //if (!char_in_set(char_, {'.'})){
          //   if (!char_in_set(char_, numchars)){
                 gears.emplace_back(Gridpos(r,c));
           //  }
          }
      }
  }

  return gears;
}

bool is_good_num( Gridpos num, const std::vector<Gridpos>& gears){

   int row = num.get_r();
   int col = num.get_c();
   int k   = num.get_v();
   auto kstr = std::to_string(k);
   int klen  = (int) kstr.length();

   auto ics = get_list_range(col-1, col+klen+1);
   auto irs = get_list_range(row-1, row+2);

   for (auto& ir : irs){
     for (auto& ic : ics){
       //std::tuple<int,int> val = {ir, ic};
       Gridpos val(ir, ic);
       for (const auto& gear: gears){
         if (val == gear){
             return true;
         }
       }
     }
   }
   return false;
}

void count_gears_p1(const std::vector<Gridpos>& gears,  std::vector<Gridpos> nums){

  std::vector<int> good_nums;

  for (auto& num : nums){
      if (is_good_num(num, gears))
        good_nums.push_back(num.get_v());
  }

  auto ans = std::accumulate(good_nums.begin(), good_nums.end(), 0);
  std:: cout << ans << "\n";
}

std::vector<Gridpos> get_star_gears(const std::vector<std::string>& lines){
  std::vector<Gridpos> gears;

  for (auto r = 0ul; r < lines.size(); ++r){
      auto line = lines[r];
      for (auto c = 0ul; c < line.length(); ++c){
          char char_ = line[c];
          if (char_ == '*'){
                 gears.emplace_back(Gridpos(r,c));
          }
      }
  }

  return gears;
}


Gridpos get_gear( Gridpos num, const std::vector<Gridpos>& gears){

   int row = num.get_r();
   int col = num.get_c();
   int k   = num.get_v();
   auto kstr = std::to_string(k);
   int klen  = (int) kstr.length();

   auto ics = get_list_range(col-1, col+klen+1);
   auto irs = get_list_range(row-1, row+2);

   for (auto& ir : irs){
     for (auto& ic : ics){
       Gridpos val(ir, ic);
       for (const auto& gear: gears){
         if (val == gear){
             return val;
         }
       }
     }
   }
   return Gridpos(-1,-1);
}


void erase_non_gears(std::map<Gridpos, std::vector<Gridpos>>& gmap) {

  for (auto it = std::begin(gmap); it != std::end(gmap); ) {
      if (it->second.size() != 2){
          it = gmap.erase(it);
      } else {
          ++it;
      }
  }
}

auto get_gear_map(const std::vector<Gridpos>& gears,  std::vector<Gridpos> nums) -> std::map<Gridpos,std::vector<Gridpos>>{

  std::map<Gridpos, std::vector<Gridpos>> gmap;
  for (const auto& gear: gears){
      gmap[gear] = std::vector<Gridpos>();
  }

  for (auto& num : nums){
      auto gear = get_gear(num, gears);
      if (gear.get_r() != -1){
          gmap[gear].push_back(num);
      }
  }
  erase_non_gears(gmap);

  return gmap;
}

auto count_gear_ratios(std::map<Gridpos, std::vector<Gridpos>>& gmap ) -> unsigned long {

  unsigned long ans = 0;

  for (const auto& [key, vals]: gmap)
          ans += vals[0].get_v() * vals[1].get_v();

  std::cout << ans << "\n";
  return ans;
}


void solve_day03(const std::string &fname)
{
  auto lines = get_lines(fname);
  auto nums  = get_nums(lines);

  auto all_gears  = get_all_gears(lines);
  auto star_gears = get_star_gears(lines);

  auto gmap = get_gear_map(star_gears, nums);

  count_gears_p1(all_gears, nums);

  count_gear_ratios(gmap);

}
