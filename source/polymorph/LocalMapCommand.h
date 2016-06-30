#ifndef LOCAL_MAP_COMMAND_H
#define LOCAL_MAP_COMMAND_H

#include "BackendCommand.h"
#include "Playground.h"
#include "PartyMember.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "QuestMonster.h"
#include "Attack.h"
#include "Move.h"
#include "prototypes.h"

class LocalMapCommand: public BackendCommand {
  public:
    LocalMapCommand(Playground* playground, AliveGameObject* sender, AliveGameObject* target, bool is_forward);
    virtual ~LocalMapCommand();
    int add_into_queue();
    int add_frontend_callback(/*place here code to transfer frontend command into query*/);
	int execute();
  protected:
    AliveGameObject* _sender;
	AliveGameObject* _target;
	Playground* _playground;
	bool _is_forward;
};

#endif
