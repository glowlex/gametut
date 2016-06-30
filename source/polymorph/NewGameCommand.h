#ifndef NEW_GAME_COMMAND_H
#define NEW_GAME_COMMAND_H

#include "BackendCommand.h"
#include "Playground.h"

class NewGameCommand: public BackendCommand {
  public:
    NewGameCommand(Playground* playground, char* &name);
    virtual ~NewGameCommand();
    int execute();
  protected:
    Playground* _playground;
	char* _player_squad_name;
    // int _player_pic_id;
};

#endif
