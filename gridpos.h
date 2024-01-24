#ifndef GRIDPOS_H
#define GRIDPOS_H

#include <tuple>
#include <ostream>


class Gridpos
{
  int m_r = 0;
  int m_c = 0;
  int m_v = 0;
public:
  Gridpos(int r, int c, int v);
  Gridpos(int r, int c);
  Gridpos();

  int get_r() const {    return m_r;  }
  int get_c() const {    return m_c;  }
  int get_v() const {    return m_v;  }


  friend std::ostream& operator<<(std::ostream &os, const Gridpos &gp);

  friend bool operator<(const Gridpos& l, const Gridpos& r){
    return std::tie(l.m_r, l.m_c) < std::tie(r.m_r, r.m_c);
  }
  friend bool operator>(const Gridpos& l, const Gridpos& r){
    return r < l;
  }
  friend bool operator<=(const Gridpos& l, const Gridpos& r){
    return !(l > r);
  }
  friend bool operator>=(const Gridpos& l, const Gridpos& r){
    return !(l < r);
  }
  friend bool operator==(const Gridpos& l, const Gridpos& r){
    return std::tie(l.m_r, l.m_c) == std::tie(r.m_r, r.m_c);
  }
  friend bool operator!=(const Gridpos& l, const Gridpos& r){
    return !(l == r);
  }
};

class HashFn {
public:
  std::size_t operator()(const Gridpos& g) const {
    auto r = g.get_r();
    auto c = g.get_r();
    auto v = g.get_r();
    return r*150 + c + 1000*v;
  }

};

#endif // GRIDPOS_H
