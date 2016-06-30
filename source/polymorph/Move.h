#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
#include "Squad.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"

class Move: public Action {
  public:
    Move(AliveGameObject* sender, bool is_forward);
    virtual ~Move();
    
	AliveGameObject* get_sender();
    AliveGameObject* get_target() { return 0; }
	void set_sender(AliveGameObject* value);
    bool get_is_forward() { return _is_forward; }    
    int implement();
  protected:
  	AliveGameObject* _sender;
  	bool _is_forward;
};

#endif
