#include "Move.h"

Move::Move(AliveGameObject* sender, bool is_forward): Action() {
  _sender = sender;
  _is_forward = is_forward;
}

Move::~Move() {
  delete _sender;
}

AliveGameObject* Move::get_sender() {
  return _sender;
}

void  Move::set_sender(AliveGameObject* value) {
  if (value != NULL) {
    _sender = value;
  }
}

int Move::implement() {
  int* sender_health = _sender->get_health();
  if (sender_health[CURRENT_VALUE_INDEX] <= 0) {
    return 0;
  }
  delete[] sender_health;
  if (_is_forward) {
    _sender->set_coord((_sender->get_coord(0) + BASIC_SPEED), CURRENT_VALUE_INDEX);
    if (_sender->get_coord(0) >= LOCAL_MAP_WIDTH) {
      _sender->set_coord((LOCAL_MAP_WIDTH - 1), 0);
	}
  } else {
    _sender->set_coord(_sender->get_coord(0) - BASIC_SPEED, CURRENT_VALUE_INDEX);
    if (_sender->get_coord(0) < 0) {
      _sender->set_coord(0, 0);
	}
  }
  //place frontend comand here
  return 0;
}
