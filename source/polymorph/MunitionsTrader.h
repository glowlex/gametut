#ifndef MUNITIONS_TRADER_H
#define MUNITIONS_TRADER_H

#include "Trader.h"
#include "Forge.h"
#include "Item.h"
#include <cstdlib>
#include <ctime>

#pragma once

class MunitionsTrader: public Trader {
  public:
    MunitionsTrader(): Trader() {}
    MunitionsTrader(TNPCPrototype &prototype, int level);
    virtual ~MunitionsTrader();

  protected:
  	int form_assortment(TNPCPrototype &prototype, int level);
};

#endif
