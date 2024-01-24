
#include "days.h"
#include "aoc_lib.h"
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;
using std::tuple;
using std::pair;

class io_rng {
  uint64_t m_dst;
  uint64_t m_src;
  uint64_t m_sz;

public:
  io_rng(uint64_t dst, uint64_t src, uint64_t sz):
    m_dst(dst), m_src(src), m_sz(sz) {}
  uint64_t get_dst() const { return m_dst;}
  uint64_t get_src() const { return m_src;}
  uint64_t get_sz()  const { return m_sz;}
  void set_dst(uint64_t v)  { m_dst=v;}
  void set_src(uint64_t v)  { m_src=v;}
  void set_sz(uint64_t v)   { m_sz=v;}

};

class rng_fun {
  vector<io_rng> m_rngs;

public:
  rng_fun(vector<io_rng>& rngs): m_rngs(rngs){}

  vector<io_rng>& get_ranges() { return m_rngs;}

  void apply_range(vector<pair<uint64_t,uint64_t>>& R){
    vector<pair<uint64_t,uint64_t>> A;
    for (auto rng: m_rngs){
       vector<pair<uint64_t,uint64_t>> NR;

       auto dest = rng.get_dst();
       auto src = rng.get_src();
       auto sz = rng.get_sz();
       auto src_end = src+sz;

       while(R.size()){
           auto [st, ed] = R.back();
           R.pop_back();
           auto before = std::make_pair(st, std::min(ed, src));
           auto inter = std::make_pair(std::max(st, src), std::min(src_end, ed));
           auto after = std::make_pair(std::max(src_end, st), ed);
           if (before.second > before.first)
               NR.push_back(before);
           if (inter.second > inter.first)
               A.push_back(std::make_pair(inter.first-src+dest, inter.second-src+dest));
           if (after.second > after.first)
               NR.push_back(after);
       }
       R = NR;
    }
    R.insert(R.end(), A.begin(), A.end());
  }
};

uint64_t find_line(const vector<string>& lines, const string& str, uint64_t istart=0ull){

  for(auto i = istart; i < lines.size(); ++i){
      auto line = lines[i];
      auto pos = line.find(str);
      if (pos < line.size())
          return i;
  }
  return lines.size();
}

vector<io_rng> get_ranges(vector<string>& lines){
  vector<io_rng> rngs;

  // remove initial blank lines
  auto i_map = find_line(lines, "map");
  auto title = lines[0];
  lines.erase(lines.begin(), lines.begin()+i_map+1);

  auto i = 0ull;
  for (; i < lines.size(); ++i){
      auto line = lines[i];
      auto len = line.size();
      if (len == 0){
          break;
      } else{
          auto sv = split_str(line, " ");
          uint64_t d = std::stoull(sv[0]);
          uint64_t s = std::stoull(sv[1]);
          uint64_t l = std::stoull(sv[2]);
          rngs.emplace_back(io_rng(d,s,l));
      }
  }
  lines.erase(lines.begin(), lines.begin()+i);

  return rngs;
}


vector<uint64_t> get_seeds(std::string& line){
  auto sv0 = split_str(line, ":");
  auto s1 = sv0[1];
  auto sv1 = split_str(s1, " ");

  vector<uint64_t> seeds;

  for (const auto & si: sv1)
      seeds.emplace_back(std::stoull(si));

  return seeds;
}

vector<rng_fun> get_range_functions(std::vector<string>& lines){
  vector<rng_fun> vrfs;

  while (lines.size() > 2) {
    auto vrngs = get_ranges(lines);
    vrfs.emplace_back(rng_fun(vrngs));
  }

  return vrfs;
}

vector<pair<uint64_t, uint64_t>> get_seed_pairs(vector<uint64_t> seeds){

  vector<pair<uint64_t, uint64_t>> pairs;

  for(auto i = 0ull; i < seeds.size(); i += 2ull){
      auto st = seeds[i];
      auto sz = seeds[i+1];
      pairs.emplace_back(std::make_pair(st,sz));
  }

  return pairs;
}

void solve_day05(const std::string &fname)
{
  auto lines = get_lines(fname);
  lines.push_back("");
  auto seeds = get_seeds(lines[0]);
  auto pairs = get_seed_pairs(seeds);

  auto vrfs = get_range_functions(lines);

  vector<uint64_t> P2;

  for(auto& [st,sz]: pairs){

      vector<pair<uint64_t, uint64_t>> R;
      R.push_back(std::make_pair(st,st+sz));
      for(auto& rf: vrfs)
          rf.apply_range(R);

      auto imin = std::min_element(std::begin(R), std::end(R),
          [](auto lhs, auto rhs){ return lhs.first < rhs.first;});
      P2.push_back((*imin).first);
  }
  auto imin = std::min_element(P2.begin(), P2.end());
  auto minval = *imin;

  std::cout << "minval: " << minval << "\n";

}
