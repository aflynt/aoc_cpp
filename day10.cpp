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

class Tile{

public:
  Tile(): Tile( -1, -1, '.') {}
  Tile(int r, int c): Tile( r, c, '.') {}
  explicit Tile( char c ): Tile( 0, 0, c) {}
  Tile( int r, int c, char ch)
  : m_r(r), m_c(c), m_v(ch) {
    if      (m_v == '|') { m_con_n = 1; m_con_s = 1; m_con_e = 0; m_con_w = 0; }
    else if (m_v == '-') { m_con_n = 0; m_con_s = 0; m_con_e = 1; m_con_w = 1; }
    else if (m_v == 'L') { m_con_n = 1; m_con_s = 0; m_con_e = 1; m_con_w = 0; }
    else if (m_v == 'J') { m_con_n = 1; m_con_s = 0; m_con_e = 0; m_con_w = 1; }
    else if (m_v == '7') { m_con_n = 0; m_con_s = 1; m_con_e = 0; m_con_w = 1; }
    else if (m_v == 'F') { m_con_n = 0; m_con_s = 1; m_con_e = 1; m_con_w = 0; }
    else if (m_v == '.') { m_con_n = 0; m_con_s = 0; m_con_e = 0; m_con_w = 0; }
    else                 { m_con_n = 1; m_con_s = 1; m_con_e = 1; m_con_w = 1; } // S
  }

  std::pair<int, int> get_rc() const { return std::make_pair(m_r, m_c); }
  int get_r() const { return m_r; }
  int get_c() const { return m_c; }
  int get_v() const { return m_v; }
  bool connects_to_n() const { return m_con_n; }
  bool connects_to_s() const { return m_con_s; }
  bool connects_to_e() const { return m_con_e; }
  bool connects_to_w() const { return m_con_w; }

  friend std::ostream& operator<<(std::ostream &os, const Tile &ti){

    os << ti.m_r << '_' << ti.m_c << '_' << ti.m_v;

    return os;
  }

private:
  int  m_r = 0;
  int  m_c = 0;
  char m_v = '.';
  bool m_con_n = false;
  bool m_con_s = false;
  bool m_con_e = false;
  bool m_con_w = false;

};

Tile find_start_tile(vector<string> G){

  // start is an 'S'
  for(int i = 0; i < G.size(); ++i){
    auto& row = G[i];
    for(int j = 0; j < row.size(); ++j){
      char c = row[j];
      if (c == 'S'){
        return Tile(i,j,'S');
      }
    }
  }
  return Tile();
}

vector<Tile> get_valid_nbrs(const Tile& st, const vector<string>& G){
    int si = st.get_r();
    int sj = st.get_c();

    int row_n = si-1;
    int row_s = si+1;
    int row_e = si;
    int row_w = si;

    int col_n = sj;
    int col_s = sj;
    int col_e = sj+1;
    int col_w = sj-1;

    char cn = G[row_n][col_n];
    char cs = G[row_s][col_s];
    char ce = G[row_e][col_e];
    char cw = G[row_w][col_w];

    auto tn = Tile(row_n,col_n, cn);
    auto ts = Tile(row_s,col_s, cs);
    auto te = Tile(row_e,col_e, ce);
    auto tw = Tile(row_w,col_w, cw);

    vector<Tile> valid_nbrs;
    if (tn.connects_to_s() && st.connects_to_n()) { valid_nbrs.push_back(tn);}
    if (ts.connects_to_n() && st.connects_to_s()) { valid_nbrs.push_back(ts);}
    if (te.connects_to_w() && st.connects_to_e()) { valid_nbrs.push_back(te);}
    if (tw.connects_to_e() && st.connects_to_w()) { valid_nbrs.push_back(tw);}

    return valid_nbrs;
}

void get_next_tile(Tile& nt, Tile& lt, vector<string>& G){
  auto vnc = get_valid_nbrs(nt, G);
  auto vn0 = vnc[0];
  auto vn1 = vnc[1];
  auto ltrc = lt.get_rc();
  auto vn0_rc = vn0.get_rc();
  bool vn0_last = vn0_rc == ltrc;
  lt = nt;

  if (!vn0_last) {
    nt = vn0;
  } else {
    nt = vn1;
  }

}

void D10::solve_day(const std::string& fname) {

    auto G = get_lines(fname);
    auto st = find_start_tile(G);

    auto vns = get_valid_nbrs(st, G);

    int steps = 1;

    auto lt0 = st;
    auto lt1 = st;
    auto nt0 = vns[0];
    auto nt1 = vns[1];

    bool same_same = nt0.get_rc() == nt1.get_rc();
    while (!same_same){
      get_next_tile(nt0, lt0, G);
      get_next_tile(nt1, lt1, G);
      ++steps;
      //std::cout << "from " << lt0 << " -> " << nt0 << ", ";
      //std::cout            << lt1 << " -> " << nt1 << ", ";
      //std::cout << "steps: " << steps << std::endl;
      same_same = nt0.get_rc() == nt1.get_rc();
    }
    std::cout << steps << std::endl;
}
