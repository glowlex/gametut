#include "AliveGameObject.h"

AliveGameObject::AliveGameObject(): GameObject() {
  _health = new int[PAIR_ARR_SIZE] {0};
  _exp = new int[PAIR_ARR_SIZE] {0};
  _coords = new int[PAIR_ARR_SIZE] {FREE_INDEX, FREE_INDEX};
  //_equipped = NULL;
}

AliveGameObject::~AliveGameObject() {
  delete[] _coords;
  delete[] _health;
  delete[] _exp;
}

int* AliveGameObject::get_health() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _health[i];
  }
  return result;
}

int AliveGameObject::set_health(int change) {
  _health[CURRENT_VALUE_INDEX] += change;
  if (_health[CURRENT_VALUE_INDEX] < 0) {
    _health[CURRENT_VALUE_INDEX] = 0;
  } else {
    if (_health[CURRENT_VALUE_INDEX] > _health[MAXIMAL_VALUE_INDEX]) {
      _health[CURRENT_VALUE_INDEX] = _health[MAXIMAL_VALUE_INDEX];
	}
  }
  return 0;
}

int* AliveGameObject::get_exp() {
  int* result = new int[PAIR_ARR_SIZE];
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    result[i] = _exp[i];
  }
  return result;
}

int* AliveGameObject::get_coords() {
  if (_coords != NULL) {
    int* result = new int[PAIR_ARR_SIZE] {_coords[0], _coords[1]};
    return result;
  } else {
    return NULL;
  }
}

int AliveGameObject::get_coord(int index) {
  if (index > FREE_INDEX && index < PAIR_ARR_SIZE) {
    return _coords[index];
  } else {
    return FREE_INDEX;
  }
}

int AliveGameObject::set_coords(int* value) {
  if (value != NULL) {
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      _coords[i] = value[i];
	}
	delete[] value;
	return 0;
  } else {
    return FREE_INDEX;
  }
}

int AliveGameObject::set_coord(int value, int index) {
  if (index > FREE_INDEX && index < PAIR_ARR_SIZE) {
    _coords[index] = value;
    return 0;
  } else {
    return FREE_INDEX;
  }
}

int AliveGameObject::change_coords(int* value) {
  if (value != NULL) {
    for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
      _coords[i] += value[i];
	}
	delete[] value;
	return 0;
  } else {
    return FREE_INDEX;
  }
}

int AliveGameObject::change_coord(int value, int index) {
  if (index > FREE_INDEX && index < PAIR_ARR_SIZE) {
    _coords[index] += value;
    return 0;
  } else {
    return FREE_INDEX;
  }
}

int AliveGameObject::reset_coords() {
  if (_coords != NULL) {
    _coords[0] = FREE_INDEX;
    _coords[1] = FREE_INDEX;
  } else {
    _coords = new int[PAIR_ARR_SIZE] { FREE_INDEX, FREE_INDEX };
  }
  return 0;
}

int AliveGameObject::count_extra_damage(int basic_damage) {
  srand(static_cast<unsigned int>(time(0)));
  int full_damage = basic_damage;
  int dice_roll = rand() % PERCENT_MOD_CAP;
  if (dice_roll < BASE_CRITICAL_HIT_CHANCE) {
    double tmp = full_damage;
    tmp *= CRITICAL_DAMAGE_MODIFIER;
    full_damage = round(tmp);
  }
  return full_damage;
}
