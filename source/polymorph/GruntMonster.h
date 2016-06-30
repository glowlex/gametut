#ifndef GRUNTMONSTER_H
#define GRUNTMONSTER_H

#include "Monster.h"
#include "Move.h"
#include "Attack.h"

class GruntMonster: public Monster {
  public:
  	GruntMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
  	virtual ~GruntMonster();
    int decision(Squad* enemies, Action* &turn);
};

#endif
