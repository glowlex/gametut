#include "Battlefield.h"

Battlefield::Battlefield() {
  _stash = NULL;
  _player = NULL;
  _squads = NULL;
  _turn_queue = NULL;
  _turn_no = 0;
}

Battlefield::Battlefield(Location* location, Player* &player) {
  if (location != NULL) {
    _player = player;
  	_stash = NULL;
  	_squads = NULL;
  	_turn_queue =new Action*[ACTIONS_PER_TURN * (MONSTER_SQUAD_SIZE + PLAYER_SQUAD_SIZE)] {NULL};
    int fact_level; 
	location->count_fact_level(fact_level);
	srand(static_cast<unsigned int>(time(0)));
	int rnd = rand() % MAX_MONSTER_SQUADS;
	int* pack_id = NULL;
	location->get_pack_info(pack_id, rnd);
	_squads = new Squad(1, MONSTER_SQUAD_SIZE);
	spawn_new_pack(pack_id[0], false, fact_level, 1);
  }
}

Battlefield::~Battlefield() {
  delete _stash;
  _player = NULL;
  for (size_t i = 0; i < ACTIONS_PER_TURN * (MONSTER_SQUAD_SIZE + PLAYER_SQUAD_SIZE); ++i) {
    if (_turn_queue[i] != NULL) {
      delete _turn_queue[i];
	}
  }
  delete[] _turn_queue;
  delete _squads;
}

int Battlefield::spawn_new_pack(int monster_id, bool target_there, int level, int squad_id) {
  int response;
  srand(static_cast<unsigned int>(time(0)));
  if (squad_id > PLAYER_SQUAD_ID && squad_id < (MAX_MONSTER_SQUADS + 1)) {
    Forge* forge = new Forge("classic2.db");
    int rnd;
    int spawned = 0;
    for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
      rnd = rand() % PERCENT_MOD_CAP;
      if (rnd <= (PERCENT_MOD_CAP - spawned * SPAWN_CHANCE_DECREMENT)) {
      	delete _squads->_members[spawned];
      	response = forge->MakeMonster(monster_id, level, &(_squads->_members[spawned]));
      	++spawned;
	  } else {
        break;
	  }
	}
    delete forge;
  }
  return response;
}

int Battlefield::pack_set_leader() {
  if (_squads != NULL) {
    for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
      if (_squads->_members[i] != NULL && !_squads->_members[i]->get_is_leader()) {
        _squads->_members[i]->try_make_leader();
      }
	}
  }
  return 0;
}

int Battlefield::set_mass_leader() {
  for (size_t i = 0; i < MAX_MONSTER_SQUADS / MAX_MONSTER_SQUADS; ++i) {
  	bool already_spawned;
  	mass_leader_is_spawned(already_spawned);
  	if (already_spawned) {
      break;
    }
    if (_squads != NULL) {
      int leader_index;
      pack_has_leader(leader_index);
      if (leader_index > FREE_INDEX) {
        _squads->_members[leader_index]->try_make_mass_leader();
	  }
	}
  }
  return 0;
}

int Battlefield::pack_has_leader(int &result_index) {
  result_index = FREE_INDEX;
  if (_squads != NULL) {
    for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
      if (_squads->_members[i] != NULL) {
        if (_squads->_members[i]->get_is_leader()) {
          result_index = i;
          break;
	    }
	  }
    }
  }
  return 0;
}

int Battlefield::mass_leader_is_spawned(bool &result) {
  result = false;
  if (_squads != NULL) {
    for (size_t j = 0; j < MONSTER_SQUAD_SIZE; ++j) {
      if (_squads->_members[j] != NULL) {
        result = _squads->_members[j]->get_is_mass_leader();
      }
	  if (result) {
        break;
	  }
	}
  }
  return 0;
}

int Battlefield::enemy_turn() {
  
  return 0;
}

int Battlefield::make_turn() {
  ++_turn_no;
  sort_turn_queue();
  for (size_t i = 0; i < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MONSTER_SQUAD_SIZE)); ++i) {
    _turn_queue[i]->implement();
    delete _turn_queue[i];
  }
  clear_dead();
  return 0;
}

int Battlefield::if_end_fight(bool &is_victory, bool &is_end) {
  is_victory = true;
  is_end = false;
  int player_alive = 0;
  _player->_squad->count_alive(player_alive);
  if (player_alive == 0) {
  	is_victory = false;
  	is_end = true;
  } else {
  	int sum_enemies_alive = 0;
    if (_squads != NULL) {
      int squad_alive = 0;
      _squads->count_alive(squad_alive);
      sum_enemies_alive += squad_alive;
    }
    if (sum_enemies_alive == 0) {
      is_end = true;
      is_victory = true;
    }
  }
  return 0;
}

int Battlefield::place_units_on_map() {
  int seed = LOCAL_MAP_WIDTH / 8;
  srand(static_cast<unsigned int>(time(0)));
  for (size_t i = 0; i < PLAYER_SQUAD_SIZE; ++i) {
    int rnd = rand() % seed;
    if(_player->_squad->_members[i] != NULL) {
      _player->_squad->_members[i]->set_coord(rnd, 0);
    }
  }
  for (size_t i = 0; i < MONSTER_SQUAD_SIZE; ++i) {
    int rnd = rand() % seed;
    if (_squads->_members[i] != NULL) {
      _squads->_members[i]->set_coord(LOCAL_MAP_WIDTH - 1 - rnd, 0);
	}
  }
  return 0;
}

int Battlefield::clear_dead() {
  for (size_t i = 0; i <  PLAYER_SQUAD_SIZE; ++i) {
    if (_player->_squad->_members[i] != NULL) {
      int* health = _player->_squad->_members[i]->get_health();
      if (health[CURRENT_VALUE_INDEX] <= 0) {
        _player->change_cash(FREE_INDEX * CRITICAL_DAMAGE_MODIFIER * _player->_squad->_members[i]->get_salary());
        for (size_t j = 0; j < ES_SIZE; ++i) {
          PartyMember* tmp = dynamic_cast<PartyMember*>(_player->_squad->_members[i]);
          Equipped* inv = dynamic_cast<Equipped*>(tmp->_equipped);
          _stash->_stash.push_back(inv->_content[j]);
	    }
        delete _player->_squad->_members[i];
      }
      delete[] health;
    }
  }
  for (size_t j = 0; j < MONSTER_SQUAD_SIZE; ++j) {
    if (_squads->_members[j] != NULL) {
      int* health = _squads->_members[j]->get_health();
      if (health[CURRENT_VALUE_INDEX] <= 0) {
        generate_loot(_stash, _squads->_members[j]->get_loot_list(), _squads->_members[j]->get_level(), _squads->_members[j]->get_is_leader(), _squads->_members[j]->get_is_mass_leader());
        delete _squads->_members[j];
	  }
      delete[] health;
	}
  }
  return 0;
}

int Battlefield::generate_loot(Stash* &stash, int _loot_list, int _level, bool _is_leader, bool _is_mass_leader) {
  int response;
  int range = 2 * LEVEL_RANGE;
  srand(static_cast<unsigned int>(time(0)));
  Forge* forge = new Forge("classic2.db");
  TLootList list;
  list._loot = NULL;
  if (_loot_list != FREE_INDEX) {
  	response = forge->MakeLootList(_loot_list, &list);
  } else {
    response = forge->MakeLootList(rand() % LOOT_LISTS_COUNT + 1, &list);	
  }
  for (size_t i = 0; i < LOOT_LIST_SIZE; ++i) {
    if (list._loot[i]._id != FREE_INDEX) {
      for (size_t i = 0; i < list._loot[i]._max_quant; ++i) {
        int rnd = rand() % PERCENT_CAP;
        if (rnd <= list._loot[i]._chance) {
          Item* new_item = NULL;
          int item_level = _level + (rand() % range - LEVEL_RANGE);
          response = forge->MakeItem(list._loot[i]._id, item_level, &new_item);
          stash->_stash.push_back(new_item);
          new_item = NULL;
		}
	  }
	}
  }
  delete forge;
  for (size_t i = 0; i < _level; ++i) {
    double tmp = list._cash;
    tmp *= CASH_RAISE;
    list._cash = round(tmp);
    tmp = list._exp;
    tmp *= EXP_RAISE;
    list._exp = round(tmp);
  }
  if (_is_leader) {
    double tmp = list._cash;
    tmp *= LEADER_CASH_MODIFIER;
    list._cash = round(tmp);
    tmp = list._exp;
    tmp *= LEADER_EXP_MODIFIER;
    list._exp = round(tmp);
    if (_is_mass_leader) {
      tmp = list._cash;
      tmp *= MASS_LEADER_CASH_MODIFIER;
      list._cash = round(tmp);
      tmp = list._exp;
      tmp *= MASS_LEADER_EXP_MODIFIER;
      list._exp = round(tmp);
	}
  }
  stash->add_cash(list._cash);
  stash->add_exp(list._exp);
  return response;
}


int Battlefield::sort_turn_queue() {
  for (size_t i = 0; i < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MONSTER_SQUAD_SIZE)) - 1; ++i) {
  	int max_index = i;
    for (size_t j = i+1; j < (ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MONSTER_SQUAD_SIZE)); ++j) {
      if (_turn_queue[max_index] == NULL) {
      	max_index = j;
	  } else {
	    if (_turn_queue[j] != NULL) {
          AliveGameObject* max_sender = _turn_queue[max_index]->get_sender();
          AliveGameObject* j_sender = _turn_queue[j]->get_sender();
          if (max_sender->get_initiative() < j_sender->get_initiative()) {
            max_index = j;
	      }
          max_sender = NULL;
          j_sender = NULL;
	    }
      }
	}
	Action* tmp = _turn_queue[max_index];
	_turn_queue[max_index] = _turn_queue[i];
	_turn_queue[i] = tmp;
	tmp = NULL;
  }
  return 0;
}
