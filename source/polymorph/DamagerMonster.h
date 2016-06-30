#ifndef DAMAGERMONSTER_H
#define DAMAGERMONSTER_H

#include "Monster.h"
#include "Move.h"
#include "Attack.h"

class DamagerMonster: public Monster {
  public:
  	DamagerMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~DamagerMonster();
    int decision(Squad* enemies, Action* &turn);
};

#endif
