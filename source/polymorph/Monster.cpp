#include "Monster.h"

Monster::Monster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level):AliveGameObject() {
  srand(static_cast<unsigned int>(time(0)));
  _damage = new int[PAIR_ARR_SIZE] {0};
  _faction = new unsigned char[NAMESTRING_SIZE] {};
  _role = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < NAMESTRING_SIZE; ++i ) {
    _name[i] = name[i];
    _faction[i] = faction[i];
  }
  _damage[CURRENT_VALUE_INDEX] = prototype._damage;
  _health[MAXIMAL_VALUE_INDEX] = prototype._hp;
  _defense = prototype._defense;
  _loot_list = prototype._loot_list_id;
  _initiative = prototype._initiative;
  _is_leader = false;
  _is_mass_leader = false;
  _morale = MAX_MORALE_VALUE;
  _in_pack_id = FREE_INDEX;
  _pic_id =  rand() % MONSTER_FACES_COUNT;
  if (_level > START_LEVEL) {
    for (size_t i = 0; i < _level; ++ i) {
      double tmp = _defense;
      tmp *= DAMDEF_LEVEL_MODIFIER;
      _defense = round(tmp);
      tmp = _damage[CURRENT_VALUE_INDEX];
      tmp *= DAMDEF_LEVEL_MODIFIER;
      _damage[CURRENT_VALUE_INDEX] = round(tmp);
      _health[MAXIMAL_VALUE_INDEX] += HP_RAISE_PER_LEVEL;
	}
  }
  _health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
  {
  	double tmp_dmg = _damage[CURRENT_VALUE_INDEX];
  	tmp_dmg *= ITEM_DAMAGE_MINMAX_RATIO;
  	_damage[MAXIMAL_VALUE_INDEX] = round(tmp_dmg);
  }
}

Monster::~Monster() {
  delete[] _damage;
  delete[] _faction;
  delete[] _role;
}

int Monster::try_make_leader() {
  srand(static_cast<unsigned int>(time(0)));
  int dice_roll = rand() % PERCENT_MOD_CAP;
  if (dice_roll <= BASE_LEADER_PROB) {
    for (size_t i = 0 ; i < PAIR_ARR_SIZE; ++i) {
      double tmp = _damage[i];
      tmp *= LEADER_DMG_MODIFIER;
      _damage[i] = round(tmp);
	}
	double tmp = _health[MAXIMAL_VALUE_INDEX];
	tmp *= LEADER_HP_MODIFIER;
	_health[MAXIMAL_VALUE_INDEX] = round(tmp);
	_health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	tmp = _defense;
	tmp *= LEADER_DEF_MODIFIER;
	_defense =round(tmp);
	_is_leader = true;
  }
  return 0;
}

int Monster::try_make_mass_leader() {
  srand(static_cast<unsigned int>(time(0)));
  int dice_roll = rand() % PERCENT_MOD_CAP;
  if (dice_roll <= BASE_MASS_LEADER_PROB && _is_leader) {
    for (size_t i = 0 ; i < PAIR_ARR_SIZE; ++i) {
      double tmp = _damage[i];
      tmp *= MASS_LEADER_DMG_MODIFIER;
      _damage[i] = round(tmp);
	}
	double tmp = _health[MAXIMAL_VALUE_INDEX];
	tmp *= MASS_LEADER_HP_MODIFIER;
	_health[MAXIMAL_VALUE_INDEX] = round(tmp);
	_health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	tmp = _defense;
	tmp *= MASS_LEADER_DEF_MODIFIER;
	_defense =round(tmp);
	_is_mass_leader = true;
  }
  return 0;
}

int Monster::count_damage() {
  srand(static_cast<unsigned int>(time(0)));
  int damage = rand() % (_damage[1] - _damage[0]) + _damage[0];
  return damage;
}

bool Monster::make_hit_roll(int distance) {
	srand(static_cast<unsigned int>(time(0)));
	bool if_hit = false;
	int hit_roll = rand() % PERCENT_MOD_CAP;
    int hit_chance = PERCENT_MOD_CAP / 2 - distance + rand() % (PERCENT_MOD_CAP / 5);
    if_hit = hit_roll <= hit_chance;
	return if_hit;  
}

int* Monster::get_damage() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _damage[i];
  }
  return result;
}
int Monster::look_around(Squad* enemies, int& closest_enemy, int& weakest_enemy) {
  get_closest(closest_enemy, enemies);
  get_weakest(weakest_enemy, enemies);
  return 0;
}

int Monster::get_closest(int& closest_enemy_id, Squad* enemies) {
  int coord;
  int distance;
  closest_enemy_id = 0;
  coord = enemies->_members[0]->get_coord(0);
  get_distance(coord, distance);
  for (size_t i = 1; i < PLAYER_SQUAD_SIZE; ++i) {
  	int distance_i;
  	coord = enemies->_members[i]->get_coord(0);
  	get_distance(coord, distance_i);
  	if (distance > distance_i) {
      distance = distance_i;
      closest_enemy_id = i;
    }
  }
  return 0;
}

int Monster::get_weakest(int& weakest_enemy_id, Squad* enemies) {
  int* health = enemies->_members[0]->get_health();
  weakest_enemy_id = 0;
  for (size_t i = 1; i < PLAYER_SQUAD_SIZE; ++i) {
    int* health_i = enemies->_members[i]->get_health();
    if (health[CURRENT_VALUE_INDEX] < health_i[CURRENT_VALUE_INDEX]) {
      health[CURRENT_VALUE_INDEX] = health_i[CURRENT_VALUE_INDEX];
      weakest_enemy_id = i;
	}
    delete[] health_i;
  }
  delete[] health;
  return 0;
}

int Monster::get_distance(int to_x, int &result) {
  int x_distance, y_distance;
  if (_coords[0] >= to_x) {
    x_distance = _coords[0] - to_x;
  } else {
    x_distance = to_x - _coords[0];
  }
  result = x_distance;
  return 0;
}

int Monster::evaluate(int& points, Squad* enemies, int id) {
  points = 0;
  srand(static_cast<unsigned int>(time(0)));
  const int NEED_TO_MOVE = 10;
  if (id > FREE_INDEX && id < PLAYER_SQUAD_SIZE) {
    if (enemies != NULL) {
      if (enemies->_members[id] != NULL) {
        int* health = enemies->_members[id]->get_health();
        double remaining_hp = health[CURRENT_VALUE_INDEX] / health[MAXIMAL_VALUE_INDEX];
        int points_hp = PERCENT_CAP * (1.0 - remaining_hp);
        points += points_hp;
        if (health[CURRENT_VALUE_INDEX] <= _damage[0]) {
          points += ONE_SHOT_MODIFIER;
		} else {
          if (health[CURRENT_VALUE_INDEX] <= _damage[1]) {
            points += ONE_SHOT_MODIFIER / 2;
		  }
		}
		int coord = enemies->_members[id]->get_coord(0);
		int distance;
		get_distance(coord, distance);
		if (distance > (_distance + BASIC_SPEED)) {
          points -= (NEED_TO_MOVE * 2);
		} else {
          if  (distance > _distance) {
            points -= NEED_TO_MOVE;
		  } else {
            int hit_chance_points = rand() % (PERCENT_CAP / 5) - distance + PERCENT_MOD_CAP / 2;
            points += hit_chance_points;
		  }
		}
        delete[] health;
	  }
	}
  }
  return  0;
}

int Monster::what(std::string &out) {
  char* digit = new char[NAMESTRING_SIZE / 2];
  out.clear();
  std::string str;
  str.clear();
  str.append((char*) _name);
  str.append("\t");
  str.append((char*) _role);
  str.append("\t level: ");
  str.append(itoa(_level, digit, 10));
  str.append("\n--\n");
  if(_is_leader) {
    str.append("pack leader\n");
  }
  if (_is_mass_leader) {
    str.append("group leader\n");
  }
  str.append("faction: ");
  str.append((char*) _faction);
  str.append("\n");
  str.append("health: ");
  str.append(itoa(_health[CURRENT_VALUE_INDEX], digit, 10));
  str.append(" / ");
  str.append(itoa(_health[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("damage: ");
  str.append(itoa(_damage[CURRENT_VALUE_INDEX], digit, 10));
  str.append(" - ");
  str.append(itoa(_damage[MAXIMAL_VALUE_INDEX], digit, 10));
  str.append("\n");
  str.append("distance: ");
  str.append(itoa(_distance, digit, 10));
  str.append("\n");
  str.append("defense: ");
  str.append(itoa(_defense, digit, 10));
  str.append("\n");
  out += str;
  delete[] digit;
  return 0;
}

int Monster::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  prefix = "monster_face_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE];
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
