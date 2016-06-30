#ifndef QUESTMONSTER_H
#define QUESTMONSTER_H

#include "Monster.h"
#include "Attack.h"
#include "Move.h"

class QuestMonster: public Monster {
  public:
  	QuestMonster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level, int quest_id);
  	virtual ~QuestMonster();
    int decision(Squad* enemies, Action* &turn);
  protected:
  	int _quest_id;
};

#endif
