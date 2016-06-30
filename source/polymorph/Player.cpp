#include "Player.h"

Player::Player() {
  Forge* forge = new Forge("classic2.db");
  _company_name = NULL;
  _bag = new Storage(BACKPACK_SIZE);
  _storage = new Storage(STORAGE_SIZE);
  _bank = new Storage(BANK_SIZE);
  _squad = new Squad(PLAYER_SQUAD_ID, PLAYER_SQUAD_SIZE);
  srand(static_cast<unsigned int>(time(0)));
  _cash = START_CASH;
  _total_earned = 0;
  int initial_mercs_count = rand() % 2 + 1;
  int response;
  for(size_t i = 0; i < initial_mercs_count; ++i) {
    AliveGameObject* tmp_mercenary = NULL;
    response = forge->MakeMercenary(rand() % MERC_PRESETS_COUNT + 1, START_LEVEL, &tmp_mercenary);
    for (size_t i = 0; i < _squad->get_max_size(); ++i) {
      if (_squad->_members[i] == NULL) {
        _squad->_members[i] = tmp_mercenary;
	  }
	}
	_squad->count_alive();
    tmp_mercenary = NULL;
  }
  delete forge;
}

Player::Player(char* name) {
  Forge* forge = new Forge("classic2.db");
  _company_name = new char[NAMESTRING_SIZE];
  if (name != NULL) {
    for (size_t i = 0; i < NAMESTRING_SIZE && name[i] != '\0'; ++i) {
      _company_name[i] = name[i];
	}
  }
  delete[] name;
  _bag = new Storage(BACKPACK_SIZE);
  _storage = new Storage(STORAGE_SIZE);
  _bank = new Storage(BANK_SIZE);
  _squad = new Squad(PLAYER_SQUAD_ID, PLAYER_SQUAD_SIZE);
  srand(static_cast<unsigned int>(time(0)));
  _cash = START_CASH;
  _total_earned = 0;
  int initial_mercs_count = rand() % 2 + 1;
  int response;
  for(size_t i = 0; i < initial_mercs_count; ++i) {
    AliveGameObject* tmp_mercenary = NULL;
    response = forge->MakeMercenary(rand() % MERC_PRESETS_COUNT + 1, START_LEVEL, &tmp_mercenary);
    for (size_t i = 0; i < _squad->get_max_size(); ++i) {
      if (_squad->_members[i] == NULL) {
        _squad->_members[i] = tmp_mercenary;
	  }
	}
	_squad->count_alive();
    tmp_mercenary = NULL;
  }
  delete forge;
}

Player::~Player() {
  delete _bag;
  delete _storage;
  delete _bank;
  delete _squad;
}

int Player::hire(AliveGameObject* new_party_member) {
  _squad->count_alive();
  if (_squad->get_alive_count() < PLAYER_SQUAD_SIZE) {
    for (size_t i = 0; i < _squad->get_max_size(); ++i) {
      if (_squad->_members[i] == NULL) {
        _squad->_members[i] = new_party_member;
        new_party_member = NULL;
        break;
	  }
	}
  }
  return 0;
}

int Player::fire(int to_fire, AliveGameObject* &to_save) {
  if (to_fire > FREE_INDEX && to_fire < PLAYER_SQUAD_SIZE) {
    if (_squad->_members[to_fire] != NULL) {
      to_save = _squad->_members[to_fire];
      _squad->_members[to_fire] = NULL;
      _squad->count_alive();
	}
  }
  return 0;
}

int Player::payday() {
  for (size_t i = 0; i < _squad->get_max_size(); ++i) {
    if (_squad->_members[i] != NULL) {
      PartyMember* merc = dynamic_cast<PartyMember*>(_squad->_members[i]);
      if (_cash >= merc->get_salary()) {
        _cash -= merc->get_salary();
        merc->reset_unpaid_count();
	  } else {
        merc->increase_unpaid_count();
        //TO-DO: if _unpaid_count reaches critical value (look for this const at in_game_objects.h) merc should leave party.
      }
	} 
  }
  return 0;
}

int Player::buy(NPC* trader, int to_buy_id) {
  if (to_buy_id > FREE_INDEX && to_buy_id < VENDOR_CAPACITY && trader != NULL) {
  	int total_count;    
  	Trader* tdr = dynamic_cast<Trader*>(trader);
  	double tmp = tdr->get_charge() / 100 + 1.0;
  	tmp *= tdr->_assortment[to_buy_id]->get_cost();
  	total_count = round(tmp);
    if (_cash >= total_count) {
      int free_space;
      _bag->count_free_slots(free_space);
      if (free_space > 0) {
      	 int first_free;
      	 _bag->first_free_slot(first_free);
      	 Storage* bag = dynamic_cast<Storage*>(_bag);
         bag->_content[first_free] = tdr->_assortment[to_buy_id];
         tdr->_assortment[to_buy_id] = NULL;
         _cash -= total_count;
	  }
	}
  }
  return 0;
}

int Player::sell(NPC* trader, int to_sell_id) {
  if (to_sell_id > FREE_INDEX && to_sell_id < BACKPACK_SIZE && trader != NULL) {
    Trader* tdr = dynamic_cast<Trader*>(trader);
    Storage* bag = dynamic_cast<Storage*>(_bag);
	double tmp = 1.0 - tdr->get_charge() / 100;
    tmp *= bag->_content[to_sell_id]->get_cost();
    int total_count = round(tmp);
    _cash += total_count;
    for (size_t i = 0; i < VENDOR_CAPACITY; ++i) {
      if (tdr->_assortment[i] == NULL) {
        tdr->_assortment[i] = bag->_content[to_sell_id];
        break;
	  }
	}
	bag->_content[to_sell_id] = NULL;
  }
  return 0;
}

int Player::get_cash(int &result) {
  result = _cash;
  return 0;
}

int Player::get_total_earned(int &result) {
  result = _total_earned;
  return 0;
}

int Player::change_cash(int value) {
  _cash += value;
  if (value > FREE_INDEX) {
    _total_earned += value;
  }
  return 0;
}

int Player::get_average_level() {
  int result = 0;
  int count = 0;
  for (size_t i = 0; i < PLAYER_SQUAD_SIZE; ++i) {
    if(_squad->_members[i] != NULL) {
      ++count;
      result += _squad->_members[i]->get_level();
	}
  }
  if (count != 0) {
    result /= count; 
  }
  return result;
}

int Player::what(std::string &out) {
  out.clear();
  char* digit = new char[NAMESTRING_SIZE / 2];
  std::string str;
  str.clear();
  str.append("Your mercenary company:\n--\n");
  str.append("Squad info:\n--\n");
  str.append("Members:\n");
  for (size_t i = 0; i < _squad->get_max_size(); ++i) {
    if (_squad->_members[i] != NULL) {
      unsigned char* tmp_name = NULL;
      tmp_name = _squad->_members[i]->get_name();
      str.append((char*) tmp_name);
      str.append("\t level: ");
      int level = _squad->_members[i]->get_level();
      str.append(itoa(level, digit, 10));
      str.append("\t salary:");
      int salary = _squad->_members[i]->get_salary();
      str.append(itoa(salary, digit, 10));
      str.append("\n--\n");
      delete[] tmp_name;
	}
  }
  str.append("--\n");
  str.append("Finances:\n--\n");
  str.append("Cash: ");
  str.append(itoa(_cash, digit, 10));
  str.append(" credits\nTotal earnings since company\'s establishment: ");
  str.append(itoa(_total_earned, digit, 10));
  str.append(" credits\n--\n");
  str.append("--\n");
  out += str;
  delete[] digit;
  return 0;
}
