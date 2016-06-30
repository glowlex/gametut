#include "NewGameCommand.h"

NewGameCommand::NewGameCommand(Playground* playground, char* &name): BackendCommand() {
  _playground = playground;
  _player_squad_name = new char[NAMESTRING_SIZE] {};
  if (name != NULL) {
    for (size_t i = 0; i < NAMESTRING_SIZE && name[i] != '\0'; ++i) {
      _player_squad_name[i] = name[i];
    }
  }
  delete[] name;
}

NewGameCommand::~NewGameCommand() {
  _playground = NULL;
  delete[] _player_squad_name;
}

int NewGameCommand::execute() {
  if (_playground == NULL) {
    _playground = new Playground(_player_squad_name);
  }
  return 0;
}
