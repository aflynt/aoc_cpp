

#include "aoc_lib.h"
#include <map>
#include <sstream>

using std::string;
using std::vector;

namespace D12 {

  uint64_t cantor(uint64_t a, uint64_t b){
    return (a+b+1)*(a+b)/2 + b;
  }

  uint64_t chash(uint64_t a, uint64_t b, uint64_t c){
    return cantor(a, cantor(b, c));
  }

  std::map<uint64_t, uint64_t> DP;
  uint64_t f(const string& dots, const vector<uint64_t>& blocks, uint64_t i, uint64_t bi, uint64_t current){
    uint64_t key = chash(i, bi, current);
    if ( auto search = DP.find(key); search != DP.end())
        return search->second;
    if (static_cast<size_t>(i) == dots.size()){
        if (static_cast<size_t>(bi) == blocks.size() && current == 0){
            return 1;
        } else if (static_cast<size_t>(bi) == blocks.size()-1 && blocks[bi]==current){
            return 1;
        } else {
            return 0;
        }
    }
    uint64_t ans = 0;
    for(char c: {'.', '#'}){
        if(dots[i]==c || dots[i] == '?') {
            if (c=='.' && current==0)
              ans += f(dots, blocks, i+1, bi, 0);
            else if (c=='.' && current>0 && bi<(uint64_t) blocks.size() && blocks[bi]==current)
              ans += f(dots, blocks, i+1, bi+1, 0);
            else if (c=='#')
              ans += f(dots, blocks, i+1, bi, current+1);
        }
    }
    DP[key] = ans;
    return ans;
  }

  void solve_p1(const vector<string>& lines){

    uint64_t ans = 0;

    for (auto& line: lines){
        auto res = split_str(line, " ");
        string dots = res[0];
        string blockstr = res[1];
        auto block_list = split_str(blockstr, ",");
        vector<uint64_t> blocks;
        std::transform(block_list.begin(), block_list.end(), std::back_inserter(blocks), [](auto& blk){return std::stoi(blk);});
        DP.clear();
        ans += f(dots, blocks, 0,0,0);
    }
    std::cout<< ans << std::endl;

  }

  void replicate_str(string& str, uint64_t count=2, const string& sep=""){
    std::stringstream ss(str);

    for(uint64_t i = 0; i < count; ++i){
        ss << str;
        ss << sep;
    }

    str = ss.str();
    str.erase(str.end()-1);
  }

  void solve_p2(const vector<string>& lines){

    uint64_t ans = 0;

    for (auto& line: lines){
        auto res = split_str(line, " ");

        string dots = res[0];
        replicate_str(dots, 5, "?");

        string blockstr = res[1];
        replicate_str(blockstr, 5, ",");

        auto block_list = split_str(blockstr, ",");

        vector<uint64_t> blocks;
        std::transform(block_list.begin(), block_list.end(), std::back_inserter(blocks), [](auto& blk){return std::stoi(blk);});

        DP.clear();

        ans += f(dots, blocks, 0,0,0);
    }
    std::cout<< ans << std::endl;

  }

  void solve_day(const std::string& fname) {

    auto lines = get_lines(fname);

    solve_p1(lines);
    solve_p2(lines);




  }




} // END NAMESPACE
