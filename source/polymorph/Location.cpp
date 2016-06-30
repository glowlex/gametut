#include "Location.h"

Location::Location(): StaticGameObject() {
  _packs = new int*[MAX_MONSTER_SQUADS] {NULL};
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    _packs[i] = new int[PAIR_ARR_SIZE] {0};
  }
}

Location::Location(TLocationPrototype &prototype, int level): StaticGameObject() {
  _low_level_cap = level - LEVEL_RANGE;
  _high_level_cap = level + LEVEL_RANGE;
  _fight_chance = prototype._fight_chance;
  _packs = new int*[MAX_MONSTER_SQUADS];
  for (size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    _packs[i] = new int[PAIR_ARR_SIZE];
    for(size_t j = 0; j < PAIR_ARR_SIZE; ++j) {
      _packs[i][j] = prototype._packs[i][j];
	}
  }
}

Location::~Location() {
  for(size_t i = 0; i < MAX_MONSTER_SQUADS; ++i) {
    delete[] _packs[i];
  }
  delete[] _packs;
}

int Location::get_pack_info(int* &result, int index) {
  delete[] result;
  if (index > FREE_INDEX && index < MAX_MONSTER_SQUADS) {
    result = new int[PAIR_ARR_SIZE] {0};
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      result[i] = _packs[index][i];
	}
  }
  return 0;
}

int Location::count_fact_level(int &result) {
  result = FREE_INDEX;
  srand(static_cast<unsigned int>(time(0)));
  int rnd = rand() % (_high_level_cap - _low_level_cap) + _low_level_cap + 1;
  result = rnd;
  return 0;
}
