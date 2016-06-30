#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "WeaponTrader.h"
#include "ArmourTrader.h"
#include "MunitionsTrader.h"
#include "BlackMarket.h"
#include "PartyMember.h"
#include "Location.h"
#include "Forge.h"

#include <cmath>
#include <ctime>
#include <cstdlib>

class Settlement: public Location {
  public:
  	Settlement(TLocationPrototype prototype, int level);
  	virtual ~Settlement();
  	
  	int entrance();
  	
  	NPC** _traders;
  	AliveGameObject** _mercs;
  	
  protected:
    int generate_traders();
    int generate_mercenaries();
};

#endif
