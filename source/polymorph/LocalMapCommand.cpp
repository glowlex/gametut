#include "LocalMapCommand.h"

LocalMapCommand::LocalMapCommand(Playground* playground, AliveGameObject* sender, AliveGameObject* target, bool is_forward): BackendCommand() {
  _sender = sender;
  _target = target;
  _playground = playground;
  _is_forward = is_forward;
}

LocalMapCommand::~LocalMapCommand() {
  _sender = NULL;
  _target = NULL;
  _playground = NULL;
}

int LocalMapCommand::add_into_queue() {
  Action* turn;
  for (size_t i = 0; i < ACTIONS_PER_TURN * (PLAYER_SQUAD_SIZE + MONSTER_SQUAD_SIZE); ++i) {
    if (_playground->_battlefield->_turn_queue == NULL) {
      turn = _playground->_battlefield->_turn_queue[i];
      break;
	}
  }
  if(_target == NULL) {
    turn = new Move(_sender, _is_forward);  
  } else {
    turn = new Attack(_sender, _target);
  }
  return 0;
}

int LocalMapCommand::add_frontend_callback(/*argument where to place frontend command there*/) {
  return 0;
}

int LocalMapCommand::execute() {
  return add_into_queue();
}
