#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Location.h"
#include "Stash.h"
#include "Squad.h"
#include "Player.h"
#include "Forge.h"
#include "Attack.h"
#include "Move.h"
#include "prototypes.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "PartyMember.h"

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>

class Battlefield {
  public:
    Battlefield();
    Battlefield(Location* location, Player* &player);
  	virtual ~Battlefield();
  	
    Squad* _squads;
    Action** _turn_queue;
    Stash* _stash;
    Player* _player;
    
    int enemy_turn();
    int make_turn();
    int if_end_fight(bool &is_victory, bool &is_end);
    
  protected:
  	int spawn_new_pack(int monster_id, bool target_there, int level, int squad_id);
  	int pack_set_leader();
  	int set_mass_leader();
  	int pack_has_leader(int &result_index);
  	int mass_leader_is_spawned(bool &result);
	int place_units_on_map();
  	int clear_dead();
  	int generate_loot(Stash* &stash, int _loot_list, int _level, bool _is_leader, bool _is_mass_leader);
  	int sort_turn_queue();	
  	int _turn_no;
};

#endif
