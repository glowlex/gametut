#include "Attack.h"

Attack::Attack(AliveGameObject* sender, AliveGameObject* target): Action(){
  _distance = count_distance(sender->get_coord(0), target->get_coord(0));
  _sender = sender;
  _target = target;
}

Attack::~Attack() {
  _sender = NULL;
  _target = NULL;
}

int Attack::implement() {
  if (_sender != NULL && _target != NULL) {
  	srand(static_cast<unsigned int>(time(0)));
    int result;
    int* sender_health = _sender->get_health();
    int* target_health = _target->get_health();
    if (target_health[CURRENT_VALUE_INDEX] <= 0 || sender_health[CURRENT_VALUE_INDEX] <= 0) {
      return 0;
	}
	delete[] sender_health;
	delete[] target_health;
	if (_distance <= _sender->get_range()) {
      if (_sender->make_hit_roll(_distance)) {
        int damage = _sender->count_extra_damage(_sender->count_damage());
        _target->set_health(FREE_INDEX * damage);
	  }
	}
  }
  return 0;
}

AliveGameObject* Attack::get_sender() {
  return _sender;
}

AliveGameObject* Attack::get_target() {
  return _target;
}

void Attack::set_sender(AliveGameObject* value) {
  	_sender = value;
}

void Attack::set_target(AliveGameObject* value) {
  _target = value;
}

int Attack::count_distance(int x1_coord, int x2_coord) {
  int distance = 0;
  if (x1_coord >= x2_coord) {
    distance += x1_coord;
    distance -= x2_coord;
  } else {
    distance += x2_coord;
    distance -= x1_coord;
  }
  return distance;
}
