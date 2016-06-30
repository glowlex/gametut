#ifndef STASH_H
#define STASH_H

#include <vector>
#include "RangedWeapon.h"
#include "MeleeWeapon.h"
#include "Head.h"
#include "Chest.h"
#include "Hands.h"
#include "Boots.h"
#include "Legs.h"
#include "Trinket.h"

class Stash {
  public:
  	std::vector<Item*> _stash;
  	
  	Stash() {}
  	virtual ~Stash() {}
  	int get_exp() { return _exp; }
  	int get_cash() { return _cash; }
  	int extract_cash(int &where_to);
  	int extract_exp(int &where_to);
  	int add_cash(int &value);
  	int add_exp(int &value);
  protected:
  	int _cash;
  	int _exp;
};

#endif
