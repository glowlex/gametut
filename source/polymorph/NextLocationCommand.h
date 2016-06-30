#ifndef NEXT_LOCATION_COMMAND_H
#define NEXT_LOCATION_COMMAND_H

#include"World.h"
#include"BackendCommand.h"

#include <ctime>
#include <cmath>
#include <cstdlib>

class NextLocationCommand: public BackendCommand {
  public:
    NextLocationCommand(Playground* playground): BackendCommand() { _playground = playground; }
    virtual ~NextLocationCommand() { _playground = NULL; }
    int execute();
  protected:
  	Playground* _playground;
};

#endif
