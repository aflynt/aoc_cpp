#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>

class card
{
  uint64_t m_id = 0;
  uint64_t m_nmatch = 0;
  uint64_t m_value = 0;
  std::vector<uint64_t> m_ws; // winning numbers
  std::vector<uint64_t> m_ns; // numbers we have

public:
  card(std::string line);

  uint64_t get_n()  const { return m_nmatch; }
  uint64_t get_id() const { return m_id; }
  uint64_t get_v() const { return m_value; }
};

#endif // CARD_H
