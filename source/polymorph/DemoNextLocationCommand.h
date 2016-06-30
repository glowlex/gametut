#ifndef  DEMO_NEXT_LOCATION_COMMAND_H
#define DEMO_NEXT_LOCATION_COMMAND_H

#include "Playground.h"
#include "BackendCommand.h"

class DemoNextLocationCommand: public BackendCommand {
  public:
    DemoNextLocationCommand(Playground* &playground): BackendCommand() { _playground = playground; }
    virtual ~DemoNextLocationCommand() { _playground = NULL; }
    int execute();
  protected:
    Playground* _playground;
};

// Note: this command written only for battle system testing purposes
// this command differs from NextLocationCommand in spawning logic: 
// demo command always spawns battles, without looking at if_fight() Location method's result

#endif
