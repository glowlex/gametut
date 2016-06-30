#ifndef FIGHT_ENDTURN_COMMAND_H
#define FIGHT_ENDTURN_COMMAND_H

#include "BackendCommand.h"
#include "Playground.h"

class FightEndTurnCommand: public BackendCommand {
  public:
  	FightEndTurnCommand(Playground* playground): BackendCommand() { _playground = playground; }
  	virtual ~FightEndTurnCommand() { _playground = NULL; }
  	int execute() { return _playground->_battlefield->make_turn(); }
  protected:
    Playground* _playground;
};

#endif
