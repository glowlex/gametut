#ifndef BACKEND_COMMAND_H
#define BACKEND_COMMAND_H

#include "Command.h"
#include "GameObject.h"

class BackendCommand: public Command {
  public:
    BackendCommand() {}
    virtual ~BackendCommand() {}
};

#endif
