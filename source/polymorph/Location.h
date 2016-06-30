#ifndef LOCATION_H
#define LOCATION_H

#include "StaticGameObject.h"

#include <cmath>
#include <ctime>
#include <cstdlib>

class Location: public StaticGameObject {
  public:
    Location();
    Location(TLocationPrototype &prototype, int level);
    virtual ~Location();
    virtual int entrance() = 0;
    int get_fight_chance() { return _fight_chance; }
    int get_low_level_cap() { return _low_level_cap; }
    int get_high_level_cap() { return _high_level_cap; }
    int get_pack_info(int* &result, int index);
    int count_fact_level(int &result);
    int if_fight() {
      srand(static_cast<unsigned int>(time(0)));
      int result = SILENCE_CODE;
      int rnd = rand() % PERCENT_MOD_CAP;
      if (rnd <= _fight_chance) {
        result = BATTLE_CODE;
      }
      return result;
    }
    int what(std::string &out) { return 0; }
  protected:
    int _fight_chance;
    int** _packs;
    int _low_level_cap;
    int _high_level_cap;
};

#endif
