#include "GruntMonster.h"

GruntMonster::GruntMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level): Monster(prototype, name, faction, level) {
  double tmp;
  const unsigned char* role = (const unsigned char*)("Grunt\0");
  for (size_t i = 0; i < NAMESTRING_SIZE && role[i] != '\0'; ++i) {
    _role[i] = role[i];
  }
  for (size_t i = 0; i < PAIR_ARR_SIZE; ++i) {
    tmp = _health[i];
    tmp *= GRUNT_HP_MODIFIER;
    _health[i] = round(tmp);
    tmp = _damage[i];
    tmp *= GRUNT_DMG_MODIFIER;
    _damage[i] = round(tmp);
  }
  tmp = _defense;
  tmp *= GRUNT_DEF_MODIFIER;
  _defense = round(tmp);
  delete[] role;
}

int GruntMonster::decision(Squad* enemies, Action* &turn) {
  srand(static_cast<unsigned int>(time(0)));
  int closest_enemy = 0;
  int weakest_enemy = 0;
  look_around(enemies, closest_enemy, weakest_enemy);
  int* points = new int[PLAYER_SQUAD_SIZE] {0};
  for (size_t i = 0; i < PLAYER_SQUAD_SIZE; ++i) {
    evaluate(points[i], enemies, i);
    if (i == closest_enemy) {
      points += CLOSEST_UNIT;
	}
	if (i == weakest_enemy) {
      points += WEAKEST_UNIT;
	}
	points += rand() % PERCENT_CAP / 10;
  }
  int maximal_points_id = 0;
  int max_points = 0;
  for (size_t i = 1; i < PLAYER_SQUAD_SIZE; ++i) {
    if (max_points < points[i]) {
      maximal_points_id = i;
      max_points = points[i];
	}
  }
  int distance = 0;
  get_distance(enemies->_members[maximal_points_id]->get_coord(0), distance);
  if (distance > _distance) {
  	bool forward = enemies->_members[maximal_points_id]->get_coord(0) > _coords[0];
  	turn = new Move(this, forward);
  	++turn;
  	if (distance - BASIC_SPEED > _distance) {
  	  turn = new Move(this, forward);	
	} else {
      turn = new Attack(this, enemies->_members[maximal_points_id]);
	}
  } else {
    turn = new Attack(this, enemies->_members[maximal_points_id]);
    ++turn;
    turn = new Attack(this, enemies->_members[maximal_points_id]);
  }
  delete[] points;
  return 0;
}

