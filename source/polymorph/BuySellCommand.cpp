#include "BuySellCommand.h"

BuySellCommand::BuySellCommand(Playground* &playground, bool is_buying, int trader_id, int item_id) : BackendCommand() {
  _playground = playground;
  _is_buying = is_buying;
  _trader_id = trader_id;
  _item_id = item_id;
}

int BuySellCommand::execute() {
  if (_playground != NULL) {
    if (_trader_id > FREE_INDEX && _trader_id < TRADERS_COUNT) {
      Settlement* curr_loc = dynamic_cast<Settlement*>(_playground->_current_location);
      if (curr_loc->_traders[_trader_id] != NULL) {
        if (_is_buying) {
          if (_item_id > FREE_INDEX && _item_id < VENDOR_CAPACITY) {
            _playground->_player->buy(curr_loc->_traders[_trader_id], _item_id);
		  }
	    } else {
          if (_item_id > FREE_INDEX && _item_id < BACKPACK_SIZE) {
            _playground->_player->sell(curr_loc->_traders[_trader_id], _item_id);
		  }
	    }
	  }
	}
  }
  return 0;
}
