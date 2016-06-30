#include "Armour.h"

  Armour::Armour(): EquipableItem() {
  }
  
  Armour::Armour(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): EquipableItem() {
    srand(static_cast<unsigned int>(time(0)));
	_defense = prototype._damdef;
    delete[] _name;
    delete[] _manufacturer_id;
    _name = new unsigned char[NAMESTRING_SIZE];
    _manufacturer_id = new unsigned char[NAMESTRING_SIZE];
	for (size_t i = 0; i < STATS_COUNT; ++i) {
	  _stat_bons[i] = prototype._stat_bons[i];
	  _stat_reqs[i] = prototype._stat_reqs[i];
	}
	for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
	}
	for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
	  _manufacturer_id[i] = prototype._manufacturer[i];
	}
	for(size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
	  _description[i] = prototype._description[i];
	}
	_kind = TEquipmentKind(prototype.kind);
	_level = level;
	_cost = prototype._cost;
	_pic_id = rand() % ITEM_PIC_VARIANTS_COUNT;
	if (_level > START_LEVEL) {
      //armour stats increasement code here
      for (size_t i = 0; i < _level; ++i) {
      	double tmp = _cost;
      	tmp *= COST_LEVEL_MODIFIER;
      	int old_value = _cost;
      	_cost = round(tmp);
      	if (_cost = old_value) {
          _cost += COST_RAISE_PER_LEVEL;
		}
      	for (size_t j = 0; j < CS_SIZE; ++j){
          tmp =  _stat_reqs[j];
          tmp *= STATS_LEVEL_MODIFIER;
          old_value = _stat_reqs[j];
          if (_stat_reqs[j] == old_value && _stat_reqs[j] != 0) {
            _stat_reqs[j] += STAT_RAISE_PER_LEVEL;
		  }
          _stat_reqs[j] = round(tmp);
          tmp = _stat_bons[j];
          old_value = _stat_bons[j];
          tmp *= STATS_LEVEL_MODIFIER;
          _stat_bons[j] = round(tmp);
          if (_stat_bons[j] == old_value && _stat_bons[j] != 0) {
            _stat_bons[j] += STAT_RAISE_PER_LEVEL;
		  }
        }
        tmp = _defense;
        old_value = _defense;
        tmp *= DAMDEF_LEVEL_MODIFIER;
        _defense = tmp;
        if (_defense == old_value && _defense != 0) {
          _defense += DAMDEF_RAISE_PER_LEVEL;
		}
	  }
	}
	//armour rarity setting code here
	int rarity_dice = rand() % PERCENT_MOD_CAP;
	double quality_modifier = 1.0;
	if (rarity_dice <= BASE_LEGENDARY_CHANCE) {
      _rarity = IR_LEGENDARY;
	} else {
      if (rarity_dice <= BASE_EPIC_CHANCE) {
        _rarity = IR_EPIC;
	  } else {
        if (rarity_dice <= BASE_RARE_CHANCE) {
          _rarity = IR_RARE;
		} else {
          if (rarity_dice <= BASE_GOOD_CHANCE) {
            _rarity = IR_GOOD;
		  } else {
            if (rarity_dice <= BASE_COMMON_CHANCE) {
              _rarity = IR_COMMON;
			} else {
              _rarity = IR_TRASH;
			}
		  }
		}
	  }
	}
	quality_modifier += (ITEM_RARITY_MODIFIER * (_rarity - 1));
	double tmp_value;
	for (size_t i = 0; i < CS_SIZE; ++i) {
      tmp_value = _stat_bons[i];
      tmp_value *= quality_modifier;
      _stat_bons[i] = round(tmp_value);
	}
	tmp_value = _defense;
	tmp_value *= quality_modifier;
	_defense = round(tmp_value);
	tmp_value = _cost;
	tmp_value *= quality_modifier;
	_cost = round(tmp_value);
  }
  
  Armour::~Armour() {}
  
  int Armour::get_defense() {
    return _defense;
  }

  TEquipmentKind Armour::get_kind() {
    return _kind;
  }
  
  int Armour::what(std::string &out) {
  	std::string stat_names[CS_SIZE] {"accuracy:","reaction:","strength:","toughness:","awareness:","intelligence","persuasion","speed"};
    std::string kind_names[EK_SIZE] {"pistol","smg","assault rifle","sniper rifle","melee","light armour","medium armour","heavy armour", "trinket"};
	std::string slot_names[ES_SIZE] {"helmet","chest","gloves","boots","leg armour","trinket ","trinket ","trinket ","trinket ","main hand ","off-hand"};
	std::string lvl;
    std::string def;
    std::string cost;
    std::string dist;
    std::string req;
    std::string bon;
    lvl = "level: ";
    def = "defense: ";
    cost = "cost: ";
    dist = "distance: ";
    req = "requirements: ";
    bon = "bonuses: ";
	std::string str;
	char* digit = new char[NAMESTRING_SIZE / 2];
	str.append(NAME_TAG);
    str.append((char*)_name);
    str.append("\n");
	str.append((char*)_manufacturer_id); 
    str.append(NAME_TAG);
    str.append("\t");
    str.append(KIND_TAG);
	str += kind_names[_kind];
	str.append(KIND_TAG);
	str.append("\n--\n");
    for (size_t i = 0; i < ES_SIZE; ++i) {
      if (_slots[i] > 0) {
        str += slot_names[i];
        str.append("\n");
      	break;
	  }
	}
	str.append(LEVEL_TAG);
    str += lvl;
	str.append(itoa(_level, digit, 10));
	str.append(LEVEL_TAG);
	str.append("\n");
	str.append(DAMDEF_TAG);
    str += def;
	str.append(itoa(_defense, digit, 10));
	str.append(DAMDEF_TAG);
	str.append("\n");
	str.append(COST_TAG);
    str += cost;
	str.append(itoa(_cost, digit, 10));
	str.append(COST_TAG);
	str.append("\n");
	str.append(REQS_TAG);
    str += req; 
	str.append("\n");
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_reqs[i] > 0) {
        str += stat_names[i];
		str.append(itoa(_stat_reqs[i], digit, 10));
        str.append("\n");
	  }
	}
	str.append(REQS_TAG);
	str.append(BONS_TAG);
	str += bon;
	str.append("\n");
    for (size_t i = 0; i < CS_SIZE; ++i) {
      if (_stat_bons[i] > 0) {
        str += stat_names[i];
		str.append(itoa(_stat_bons[i], digit, 10));
        str.append("\n");
	  }
	}
	str.append(BONS_TAG);
	str.append("\n");
	str.append(DESCR_TEXT_TAG);
	str.append("''");
	str.append((char*) _description);
	str.append("''");
	str.append(DESCR_TEXT_TAG);
	str.append("\n\n");
	delete[] digit;
	out.clear();
	out += str;
    return OK_CODE;
  }
  
