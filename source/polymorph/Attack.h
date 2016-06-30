#ifndef ATTACK_H
#define ATTACK_H

#include "Action.h"

#include "Squad.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
 
class Attack: public Action {
  public:
    Attack(AliveGameObject* sender, AliveGameObject* target);
    virtual ~Attack();
    int implement();
    AliveGameObject* get_sender();
    AliveGameObject* get_target();
    void set_sender(AliveGameObject* value);
    void set_target(AliveGameObject* value);
  protected:
  	int count_distance(int x1_coord, int x2_coord);
  	AliveGameObject* _sender;
  	AliveGameObject* _target;
  	int _distance;
};

#endif
