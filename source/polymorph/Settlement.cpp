#include "Settlement.h"

Settlement::Settlement(TLocationPrototype prototype, int level): Location(prototype, level) {
  srand(static_cast<unsigned int>(time(0)));
  _mercs = new AliveGameObject*[MAX_MERCENARIES] {NULL};
  _traders = new NPC*[TRADERS_COUNT] {NULL};
  Forge* forge = new Forge("classic2.db");
  for (size_t i = 0; i < TRADERS_COUNT; ++i) {
  	if (rand() % PERCENT_MOD_CAP <= prototype._trader_chances[i]){
      forge->MakeNPC(rand() % NPC_PRESETS_COUNT + 1, level, &_traders[i]);
    }
  }
  delete forge;
}

Settlement::~Settlement() {
  for (size_t i = 0; i < TRADERS_COUNT; ++i) {
    delete _traders[i];
  }
  for (size_t i = 0; i < MAX_MERCENARIES; ++i) {
    delete _mercs[i];
  }
  delete[] _traders;
  delete[] _mercs;
}

int Settlement::entrance() {
  generate_mercenaries();
  return if_fight();
}

int Settlement::generate_mercenaries() {
  srand(static_cast<unsigned int>(time(0)));
  Forge* forge = new Forge("classic2.db");
  int response = 0;
  for (size_t i = 0; i < MAX_MERCENARIES; ++i) {
    if (rand() % PERCENT_MOD_CAP <= PERCENT_MOD_CAP / 3) {
      int level = rand() % (_high_level_cap - _low_level_cap) + _low_level_cap + START_LEVEL;
      response = forge->MakeMercenary(rand() % MERC_PRESETS_COUNT + 1, level, &_mercs[i]);
	}
  }
  delete forge;
  return response;
}
