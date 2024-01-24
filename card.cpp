#include "card.h"
#include "aoc_lib.h"
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>

card::card(std::string line)
{

  //Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
  auto bar_LR = split_str(line, "| ");
  auto bar_L = bar_LR[0];
  auto bar_R = bar_LR[1];
  auto colon_LR = split_str(bar_L, ": ");
  auto card_LR = split_str(colon_LR[0], " ");
  auto card_num_str = card_LR[1];
  m_id = std::stoull(card_num_str);
  auto bar_R_vec = split_str(bar_R, " ");
  auto colon_R_vec = split_str(colon_LR[1], " ");

  // collect numbers we have
  for (auto& str: bar_R_vec){
      auto x = std::stoull(str);
      m_ns.push_back(x);
  }

  // collect winning numbers
  for (auto& str: colon_R_vec){
      auto x = std::stoull(str);
      m_ws.push_back(x);
  }

  // get card value
  std::vector<uint64_t> wwh; // winners we have
  for (auto& n : m_ns){
      if (auto it = std::find(m_ws.begin(), m_ws.end(), n) != std::end(m_ws)){
          wwh.push_back(n);
      }
  }
  m_nmatch = wwh.size();
  if (m_nmatch > 0)
    m_value = (uint64_t) std::floor(std::pow(2ull,m_nmatch-1ull));


}
