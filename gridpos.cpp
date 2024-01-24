#include "gridpos.h"

Gridpos::Gridpos(int r, int c, int v)
{
  m_r = r;
  m_c = c;
  m_v = v;
}

Gridpos::Gridpos(int r, int c)
{
  m_r = r;
  m_c = c;
}
Gridpos::Gridpos()
{
}


std::ostream& operator<<(std::ostream& os, const Gridpos& gp)
{
  if (gp.m_v > 0) {
    os << "(" << gp.m_r << "," << gp.m_c << "," << gp.m_v <<")";
  } else{
    os << "(" << gp.m_r << "," << gp.m_c << ")";
  }
  return os;
}
