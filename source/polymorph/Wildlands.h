#ifndef WILDLANDS_H
#define WILDLANDS_H

#include "Location.h"
#include "CollectableItem.h"

class Wildlands: public Location {
  public:
  	Wildlands() {}
  	virtual ~Wildlands() {}
  	
  	int entrance() { return if_fight(); };
	Item** _loot;
};

#endif
