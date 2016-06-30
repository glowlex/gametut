#ifndef COMMONMONSTER_H
#define COMMONMONSTER_H

#include "Monster.h"
#include "Move.h"
#include "Attack.h"

class CommonMonster: public Monster {
  public:
  	CommonMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~CommonMonster();
    int decision(Squad* enemies, Action* &turn);
};

#endif
