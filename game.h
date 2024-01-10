#ifndef GAME_H
#define GAME_H
# include <string>

class Game {
private:
  int ID = 0;
  int MAX_R = 12;
  int MAX_G = 13;
  int MAX_B = 14;
  bool possible = true;
  int res = 0;
  int power = 0;
public:
  Game(std::string game_str);
  int get_res() const {
    return res;
  }
  int get_pwr() const {
    return power;
  }
};

#endif // GAME_H
