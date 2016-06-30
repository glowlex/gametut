#pragma once

#ifndef ARMOURTRADER_H
#define ARMOURTRADER_H

#include "Trader.h"
#include "Item.h"
#include "Forge.h"
#include <cstdlib>
#include <ctime>

class ArmourTrader: public Trader {
  public:
    ArmourTrader(): Trader() {}
    ArmourTrader(TNPCPrototype &prototype, int level);
    virtual ~ArmourTrader();
    
//    Item** _assortment;

  protected:
  	int form_assortment(TNPCPrototype &prototype, int level);
};

#endif
