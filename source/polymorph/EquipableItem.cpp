#include <ctime>
#include <cstdlib>

#include "EquipableItem.h"

  EquipableItem::EquipableItem(): UsableItem() {
    _stat_bons = new int[prototypes::STATS_COUNT];
    _stat_reqs = new int[prototypes::STATS_COUNT];
    _manufacturer_id = new unsigned char[NAMESTRING_SIZE];
    _slots = new int[ES_SIZE];
    _in_bag = true;
  }

  EquipableItem::~EquipableItem() {
    delete[] _stat_bons;
    delete[] _stat_reqs;
    delete[] _manufacturer_id;
    delete[] _slots;
  }

  int* EquipableItem::get_stat_bons() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_bons[i];
	}
	return res;
  }

  int* EquipableItem::get_stat_reqs() {
    int* res = new int[prototypes::STATS_COUNT];
    for (size_t i = 0; i < prototypes::STATS_COUNT; ++i) {
      res[i] = _stat_reqs[i];
	}
	return res;
  }
  
  char* EquipableItem::get_manufacturer_id() {
  	char* res = new char[NAMESTRING_SIZE];
  	for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      res[i] = _manufacturer_id[i];
    }
    return res;
  }

  int* EquipableItem::get_slots() {
    int* res = new int[ES_SIZE];
    for (size_t i = 0; i < ES_SIZE; ++i) {
      res[i] = _slots[i];
	}
	return res;
  }
  
  bool EquipableItem::meets_stat_reqs(AliveGameObject* &user){
    int* stats = NULL;
    int* bonus = NULL;
	bool result = true;
	PartyMember* usr = dynamic_cast<PartyMember*>(user);
    stats = usr->get_stats();
    Equipped* inv = dynamic_cast<Equipped*>(usr->_equipped);
    inv->get_stat_bonus(bonus);
    for (size_t i = 0; i < CS_SIZE; ++i) {
      stats[i] += bonus[i];
      result = result && (_stat_reqs[i] <= stats[i]);
	}
	result = result && (_level <= usr->get_level());
	delete[] stats;
	delete[] bonus;
	return result;
  }
  
  int EquipableItem::use(AliveGameObject* user) {
    if (_in_bag) {
      if (meets_stat_reqs(user)) {
      	int equipped_slot = FREE_INDEX;
      	PartyMember* usr = dynamic_cast<PartyMember*>(user);
      	Equipped* inv = dynamic_cast<Equipped*>(usr->_equipped);
      	for (size_t i = 0; i < ES_SIZE; ++i) {
      	  if (_slots[i] == 1 && inv->_content[i]== NULL) {
      	    equipped_slot = i;
      	    break;
		  }
		}
        _in_bag = !_in_bag;
        inv->_content[equipped_slot] = this;
	  }
	} else {
	  return 0;
	}
	return 0;  
  }
