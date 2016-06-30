#pragma once

#ifndef WEAPONTRADER_H
#define WEAPONTRADER_H

#include "Trader.h"
#include "Item.h"
#include "Forge.h"
#include <cstdlib>
#include <ctime>

class WeaponTrader: public Trader {
  public:
    WeaponTrader(): Trader() {}
    WeaponTrader(TNPCPrototype &prototype, int level);
    virtual ~WeaponTrader();
    
 //   Item** _assortment;
    
  protected:
    int form_assortment(TNPCPrototype &prototype, int level);
};

#endif
