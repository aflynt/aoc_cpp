#include "aoc_lib.h"
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


uint64_t glcm(vector<uint64_t> numbers){
  return std::accumulate(numbers.begin(), numbers.end(), 1ULL,
            [](uint64_t x, uint64_t y){ return (x*y) / std::max(1UL,std::gcd(x,y)); });
}

class Node{

  string m_name;
  string m_lnbr;
  string m_rnbr;

public:
  Node() { m_name = "IDK"; m_lnbr = "IDK"; m_rnbr = "IDK"; }
  Node(string name, string lnbr, string rnbr)
    : m_name(name), m_lnbr(lnbr), m_rnbr(rnbr) { }

  string get_name() const { return m_name; }
  string get_lnbr() const { return m_lnbr; }
  string get_rnbr() const { return m_rnbr; }

  friend bool operator<(const Node& l, const Node& r){
    return
        std::tie(l.m_name, l.m_lnbr, l.m_rnbr)
        <
        std::tie(r.m_name, r.m_lnbr, r.m_rnbr);
  }
  friend bool operator>(const Node& l, const Node& r){ return r < l;}
  friend bool operator<=(const Node& l, const Node& r){ return !(l > r);}
  friend bool operator>=(const Node& l, const Node& r){ return !(l < r);}
  friend bool operator==(const Node& l, const Node& r){
    return
        std::tie(l.m_name, l.m_lnbr, l.m_rnbr)
        ==
        std::tie(r.m_name, r.m_lnbr, r.m_rnbr);
  }
  friend bool operator!=(const Node& l, const Node& r){ return !(l == r);}
};

class Guy {
  string m_Is;
  map<string, Node> m_nodes;
  string m_pos;
  uint64_t m_i = 0;
  uint64_t m_steps = 0;

public:
  Guy (const string& Is, map<string, Node>& nodes, const string& pos="AAA")
    : m_Is(Is), m_nodes(nodes), m_pos(pos) {}
  Guy (const string& Is, map<string, Node>&& nodes, const string& pos="AAA")
    : m_Is(Is), m_nodes(nodes), m_pos(pos) {}

  void step() {
    auto instr = m_Is[m_i];
    auto& n = m_nodes[m_pos];
    if (instr == 'L') m_pos = n.get_lnbr();
    else              m_pos = n.get_rnbr();
    ++m_i;
    if (m_i >= m_Is.size()) m_i = 0;
    ++m_steps;
  }

  bool at_end() const {

    if (m_pos.back() == 'Z') return true;

    return false;
  }

  uint64_t get_steps() const { return m_steps; }

  const string& get_pos() const { return m_pos; }

  string get_ips() const {
    string ostr;
    std::stringstream ss(ostr);

    ss << "i,pos,steps = " << m_i << " " << m_pos << " " << m_steps;
    return ss.str();

  }
};

std::ostream& operator<<(std::ostream& os, const Guy& g){

  os << g.get_ips();

  return os;
}

std::ostream& operator<<(std::ostream& os, const Node& n){

  os << "_" << n.get_name() << "_" << n.get_lnbr() << "_" << n.get_rnbr() << "_";

  return os;
}

std::pair<string, map<string,Node>> get_inodes(vector<string>& lines) {

  string Is = lines[0];
  auto lbeg = lines.begin();

  lines.erase(lbeg, lbeg+2);

  map<string, Node> nodes;
  for (const auto& line : lines) {
      auto nrest = split_str(line, " = (");
      string name = nrest[0];
      auto rest = nrest[1];

      rm_whitespace(name);

      auto noParen = std::remove(rest.begin(), rest.end(), ')');
      rest.erase(noParen, rest.end());
      auto lr = split_str(rest, ", ");
      string lnbr = lr[0];
      string rnbr = lr[1];
      auto n = Node(name, lnbr, rnbr);
      nodes.emplace(std::make_pair(name, n));
  }

  return std::make_pair(Is, nodes);
}

vector<Guy> mk_ghosts(string& Is, map<string,Node>& nodes) {

  vector<Guy> gs;

  for (auto& [k,n]: nodes) {
      if (k.back() == 'A') {
        //std::cout << "found a ghost: " << k << std::endl;
        gs.emplace_back(Guy(Is, nodes, k));
      }
  }
  return gs;
}

std::pair<string,uint64_t> find_end(Guy& g){

    auto at_end = g.at_end();
    while (!at_end) {
        g.step();

        at_end = g.at_end();
    }

    auto ostr = g.get_pos();
    auto nsteps = g.get_steps();
    return std::make_pair(ostr, nsteps);
}

void solve_p1(vector<string>& lines) {

  auto p = get_inodes(lines);
  auto Is = p.first;
  auto nodes = p.second;

  auto me = Guy(Is, std::move(nodes));

  while (me.get_pos() != "ZZZ")
      me.step();

  std::cout << me << std::endl;

}

void solve_p2(vector<string>& lines) {

  auto p = get_inodes(lines);
  auto Is = p.first;
  auto nodes = p.second;

  auto gs = mk_ghosts(Is, nodes);

  vector<uint64_t> ss;

  for (uint64_t i = 0ULL; i < gs.size(); ++i){

      auto g = gs[i];
      auto p = find_end(g);
      auto ostr = p.first;
      auto nsteps = p.second;

      //std::cout << "ghost # " << i << " " << ostr << " " << g.get_ips() << std::endl;
      ss.push_back(nsteps);
  }

  auto res = glcm(ss);
  std::cout << "LCM: " << res << std::endl;

}

void solve_day08(const std::string& fname){

  auto lines = get_lines(fname);
  vector<string> lines2;
  std::copy(lines.begin(), lines.end(), std::back_inserter(lines2));

  solve_p1(lines);
  solve_p2(lines2);


}
