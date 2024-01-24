#include "aoc_lib.h"
#include "days.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>

using std::vector;
using std::string;

enum class HAND_TYPE: uint8_t {
     FIVEOFONEKIND = 0,
     FOUROFONEKIND = 1,
     FULLHOUSE     = 2,
     THREEOFAKIND  = 3,
     TWOPAIR       = 4,
     ONEPAIR       = 5,
     HIGHCARD      = 6
};

namespace P1 {

  enum class CARD_TYPE: uint8_t {
    _A = 0,
    _K = 1,
    _Q = 2,
    _J = 3,
    _T = 4,
    _9 = 5,
    _8 = 6,
    _7 = 7,
    _6 = 8,
    _5 = 9,
    _4 = 10,
    _3 = 11,
    _2 = 12
  };
}

namespace P2 {

  enum class CARD_TYPE: uint8_t {
    _A = 0,
    _K = 1,
    _Q = 2,
    _T = 3,
    _9 = 4,
    _8 = 5,
    _7 = 6,
    _6 = 7,
    _5 = 8,
    _4 = 9,
    _3 = 10,
    _2 = 11,
    _J = 12
  };
}

HAND_TYPE get_hand_type2(const std::vector<uint64_t>& ncnts, uint64_t jcnt){

    uint64_t nmax = *std::max_element(ncnts.begin(), ncnts.end());

    int64_t numpairs = std::count_if(ncnts.cbegin(), ncnts.cend(), [](uint64_t v){ return v == 2; });

    bool has3_std = std::find_if(ncnts.cbegin(), ncnts.cend(), [](uint64_t v){ return v == 3;}) != ncnts.cend();
    bool has2_std = numpairs > 0;

    bool has5  = ((nmax + jcnt) >= 5);
    bool has4  = ((nmax + jcnt) >= 4);
    bool is_fh = (has3_std && has2_std ) || (numpairs == 2 && jcnt == 1) || (numpairs == 1 && jcnt > 1);
    bool has3  = has3_std || (has2_std && jcnt >= 1) || (jcnt >= 2);
    bool is2p  = (numpairs == 2) || (numpairs == 1 && jcnt > 0);
    bool is1p  = (numpairs >= 1) || (jcnt > 0);

    if (has5)       return HAND_TYPE::FIVEOFONEKIND;
    else if (has4)  return HAND_TYPE::FOUROFONEKIND;
    else if (is_fh) return HAND_TYPE::FULLHOUSE;
    else if (has3)  return HAND_TYPE::THREEOFAKIND;
    else if (is2p)  return HAND_TYPE::TWOPAIR;
    else if (is1p)  return HAND_TYPE::ONEPAIR;
    else            return HAND_TYPE::HIGHCARD;

}

HAND_TYPE get_hand_type1(const std::vector<uint64_t>& card_counts){

    bool has5 = false;
    bool has4 = false;
    bool has3 = false;
    bool has2 = false;

    uint64_t num_pairs = 0;

    for (auto v : card_counts) {
        if (v == 5) { has5 = true; }
        if (v == 4) { has4 = true; }
        if (v == 3) { has3 = true; }
        if (v == 2) { has2 = true; ++num_pairs;}
    }

    if      (has5)          return HAND_TYPE::FIVEOFONEKIND;
    else if (has4)          return HAND_TYPE::FOUROFONEKIND;
    else if (has3 && has2)  return HAND_TYPE::FULLHOUSE;
    else if (has3)          return HAND_TYPE::THREEOFAKIND;
    else if (num_pairs == 2)return HAND_TYPE::TWOPAIR;
    else if (num_pairs == 1)return HAND_TYPE::ONEPAIR;
    else                    return HAND_TYPE::HIGHCARD;
}


template <class CARD_TYPE>
class camel_hand {

  vector<CARD_TYPE> m_cards;
  uint64_t m_bid;
  HAND_TYPE m_hand_type;

public:
    camel_hand(const string& cards, uint64_t bid): m_bid(bid)
    {
        std::map<CARD_TYPE, uint64_t> card_counts;

        card_counts[CARD_TYPE::_A] = 0ull;
        card_counts[CARD_TYPE::_K] = 0ull;
        card_counts[CARD_TYPE::_Q] = 0ull;
        card_counts[CARD_TYPE::_J] = 0ull;
        card_counts[CARD_TYPE::_T] = 0ull;
        card_counts[CARD_TYPE::_9] = 0ull;
        card_counts[CARD_TYPE::_8] = 0ull;
        card_counts[CARD_TYPE::_7] = 0ull;
        card_counts[CARD_TYPE::_6] = 0ull;
        card_counts[CARD_TYPE::_5] = 0ull;
        card_counts[CARD_TYPE::_4] = 0ull;
        card_counts[CARD_TYPE::_3] = 0ull;
        card_counts[CARD_TYPE::_2] = 0ull;

        uint64_t jcnt = 0;

        for (auto c: cards) {
            auto ct = CARD_TYPE::_2;
            switch (c) {
               case 'A': { ct = CARD_TYPE::_A; ++card_counts[CARD_TYPE::_A]; break;}
               case 'K': { ct = CARD_TYPE::_K; ++card_counts[CARD_TYPE::_K]; break;}
               case 'Q': { ct = CARD_TYPE::_Q; ++card_counts[CARD_TYPE::_Q]; break;}
               case 'J': { ct = CARD_TYPE::_J; ++card_counts[CARD_TYPE::_J]; ++jcnt; break;}
               case 'T': { ct = CARD_TYPE::_T; ++card_counts[CARD_TYPE::_T]; break;}
               case '9': { ct = CARD_TYPE::_9; ++card_counts[CARD_TYPE::_9]; break;}
               case '8': { ct = CARD_TYPE::_8; ++card_counts[CARD_TYPE::_8]; break;}
               case '7': { ct = CARD_TYPE::_7; ++card_counts[CARD_TYPE::_7]; break;}
               case '6': { ct = CARD_TYPE::_6; ++card_counts[CARD_TYPE::_6]; break;}
               case '5': { ct = CARD_TYPE::_5; ++card_counts[CARD_TYPE::_5]; break;}
               case '4': { ct = CARD_TYPE::_4; ++card_counts[CARD_TYPE::_4]; break;}
               case '3': { ct = CARD_TYPE::_3; ++card_counts[CARD_TYPE::_3]; break;}
               case '2': { ct = CARD_TYPE::_2; ++card_counts[CARD_TYPE::_2]; break;}
            }
            m_cards.push_back(ct);
        }
        vector<uint64_t> ncnts;
        for (auto& [k,v]: card_counts)
            if (k != CARD_TYPE::_J)
                ncnts.push_back(v);

        vector<uint64_t> ncnts_1;
        for (auto& [k,v]: card_counts)
            ncnts_1.push_back(v);

        if (static_cast<uint8_t>(CARD_TYPE::_J) == 3){
            m_hand_type = get_hand_type1(ncnts_1);
        } else {
            m_hand_type = get_hand_type2(ncnts, jcnt);
        }
    }

  uint64_t get_bid() const { return m_bid; }
  vector<CARD_TYPE> get_cards() const { return m_cards; }
  HAND_TYPE get_hand_type() const { return m_hand_type; }

  friend bool operator<(const camel_hand& l, const camel_hand& r){
    return
        std::tie(l.m_hand_type, l.m_cards)
        <
        std::tie(r.m_hand_type, r.m_cards);
  }
  friend bool operator>(const camel_hand& l, const camel_hand& r){ return r < l;}
  friend bool operator<=(const camel_hand& l, const camel_hand& r){ return !(l > r);}
  friend bool operator>=(const camel_hand& l, const camel_hand& r){ return !(l < r);}
  friend bool operator==(const camel_hand& l, const camel_hand& r){
    return
        std::tie(l.m_hand_type, l.m_cards)
        ==
        std::tie(r.m_hand_type, r.m_cards);
  }
  friend bool operator!=(const camel_hand& l, const camel_hand& r){ return !(l == r);}
};

template <class CARD_TYPE>
std::ostream& operator<<(std::ostream& os, const camel_hand<CARD_TYPE>& ch){
  auto ht = ch.get_hand_type();
  string ht_str;
  switch (ht) {
    case HAND_TYPE::FIVEOFONEKIND: { ht_str = "5_of_a_kind"; break;}
    case HAND_TYPE::FOUROFONEKIND: { ht_str = "4_of_a_kind"; break;}
    case HAND_TYPE::FULLHOUSE:     { ht_str = "full__house"; break;}
    case HAND_TYPE::THREEOFAKIND:  { ht_str = "3_of_a_kind"; break;}
    case HAND_TYPE::TWOPAIR:       { ht_str = "<two__pair>"; break;}
    case HAND_TYPE::ONEPAIR:       { ht_str = "<one__pair>"; break;}
    case HAND_TYPE::HIGHCARD:      { ht_str = "<high_card>"; break;}
  }
  os << "|" << ht_str << "|";

  for (auto c: ch.get_cards()) {
      switch (c) {
         case CARD_TYPE::_A: {os << "_A_"; break;}
         case CARD_TYPE::_K: {os << "_K_"; break;}
         case CARD_TYPE::_Q: {os << "_Q_"; break;}
         case CARD_TYPE::_J: {os << "_J_"; break;}
         case CARD_TYPE::_T: {os << "_T_"; break;}
         case CARD_TYPE::_9: {os << "_9_"; break;}
         case CARD_TYPE::_8: {os << "_8_"; break;}
         case CARD_TYPE::_7: {os << "_7_"; break;}
         case CARD_TYPE::_6: {os << "_6_"; break;}
         case CARD_TYPE::_5: {os << "_5_"; break;}
         case CARD_TYPE::_4: {os << "_4_"; break;}
         case CARD_TYPE::_3: {os << "_3_"; break;}
         case CARD_TYPE::_2: {os << "_2_"; break;}
      }
  }
  return os;
}

template <class T>
vector<camel_hand<T>> get_hands(vector<string>& lines){
  vector<camel_hand<T>> hands;

  for (auto& line: lines){
      auto x = split_str(line, " ");
      auto hand = x[0];
      rm_whitespace(hand);
      auto bid = std::stoull(x[1]);

      hands.emplace_back(camel_hand<T>(hand, bid));
  }
  return hands;
}

template <class CT>
void solve(vector<string>& lines){

  auto hands = get_hands<CT>(lines);

  std::sort(hands.begin(), hands.end(), std::greater<camel_hand<CT>>());

  uint64_t tot_winnings = 0;

  for (uint64_t i = 0; i < hands.size(); ++i){
      auto& hand = hands[i];
      uint64_t rank = i+1;
      auto bid = hand.get_bid();
      uint64_t winnings = rank*bid;
      tot_winnings += winnings;
      //std::cout << "rank: " << rank << " bid: " << bid << " hand: " << hand << " won: "<< winnings << " total:  " << tot_winnings << "\n";
  }
  std::cout << tot_winnings << std::endl;
}


void solve_day07(const string &fname)
{

  auto lines = get_lines(fname);

  solve<P1::CARD_TYPE>(lines);
  solve<P2::CARD_TYPE>(lines);
}
