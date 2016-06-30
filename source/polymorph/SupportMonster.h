#ifndef SUPPORTMONSTER_H
#define SUPPORTMONSTER_H

#include "Monster.h"
#include "Move.h"
#include "Attack.h"

class SupportMonster: public Monster {
  public:
  	SupportMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~SupportMonster();
    int decision(Squad* enemies, Action* &turn);
};

#endif
