#include "aoc_lib.h"
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

namespace D13 {

  vector<vector<string>> get_plines(const string& fname){
    vector<vector<string>> ps;
    string line;
    vector<string> line_vec;
    std::ifstream istrm(fname, std::ios::in);


    if(istrm.is_open()){
        while(std::getline(istrm, line)){
            auto sz = line.size();
            if (sz > 0){
                line_vec.push_back(line);
            } else {
                ps.push_back(std::move(line_vec));
                line_vec.clear();
            }
        }
    }
    ps.push_back(std::move(line_vec));

    return ps;
  }

  vector<string> get_transpose(const vector<string>& p){
    auto NI = p.size();
    auto NJ = p[0].size();

    vector<string> tp;

    for(size_t j = 0; j < NJ; ++j){
        string row_data;
        std::stringstream ss(row_data);
        for(size_t i = 0; i < NI; ++i){
            ss << p[i][j];
        }
        string rowstr = ss.str();
        tp.push_back(std::move(rowstr));
    }
    return tp;
  }

  bool are_same(const vector<string>& b_s, const vector<string>& a_s){
    auto ib = b_s.rbegin();
    auto ia = a_s.begin();

    for (; ib != b_s.rend() && ia != a_s.end(); ++ib, ++ia){
        if (*ib != *ia)
          return false;
    }
    return true;
  }

  bool are_one_diff(const vector<string>& b_s, const vector<string>& a_s){
    uint_fast64_t ndiffs = 0;

    auto ib = b_s.rbegin();
    auto ia = a_s.begin();
    for (; ib != b_s.rend() && ia != a_s.end(); ++ib, ++ia){
        string bstr = *ib;
        string astr = *ia;
        for(size_t i =0; i < bstr.size(); ++i){
            if (bstr[i] != astr[i]){
              if (++ndiffs > 1)
                return false;
            }
        }
    }
    return (ndiffs == 1);
  }

  bool is_row_mirror(const vector<string>&p, size_t i_split, bool isp2=false){
    vector<string> b_s;
    vector<string> a_s;
    for(size_t i=0; i < p.size(); ++i){
        if (i < i_split)
          b_s.push_back(p[i]);
        else
          a_s.push_back(p[i]);
    }
    if (!isp2)
      return are_same(b_s, a_s);
    else
      return are_one_diff(b_s, a_s);
  }

  size_t get_row_mirror(const vector<string>&p, bool isp2=false){
    for (size_t i = 0; i < p.size()-1; ++i){
        size_t row = i+1;
        if(is_row_mirror(p,row, isp2))
          return row;
    }
    return 0;
  }


  uint64_t solve(const vector<vector<string>>& lines, bool ispart2=false){
    uint64_t allsum = 0;
    for (auto&rp : lines){
        auto cp = get_transpose(rp);
        auto rm = get_row_mirror(rp, ispart2);
        auto cm = get_row_mirror(cp, ispart2);
        allsum += cm + 100*rm;
    }
    return allsum;
  }


  void solve_day(const std::string& fname) {

    auto ps = get_plines(fname);

    std::cout << solve(ps, false) << std::endl;
    std::cout << solve(ps, true) << std::endl;

  }

} // END NAMESPACE
