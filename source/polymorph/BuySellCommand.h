#ifndef BUY_SELL_COMMAND_H
#define BUY_SELL_COMMAND_H

#include "Playground.h"
#include "BackendCommand.h"
#include "Player.h"

class BuySellCommand : public BackendCommand {
  public:
    BuySellCommand(Playground* &playground, bool is_buying, int trader_id, int item_id);
    virtual ~BuySellCommand() { _playground = NULL; }
    int execute();
  protected:
    Playground* _playground;
    bool _is_buying;
    int _trader_id;
    int _item_id;
};

#endif
