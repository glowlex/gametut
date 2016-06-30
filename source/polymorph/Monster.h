#ifndef MONSTER_H
#define MONSTER_H

#include "AliveGameObject.h"
#include "Item.h"
#include "Stash.h"
#include "Squad.h"
#include "Action.h"
#include "prototypes.h"

#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>

class Monster : public AliveGameObject {
  public:
    Monster(TMonsterPrototype &prototype, unsigned char* name, unsigned char* faction, int level);
	virtual ~Monster();
    virtual int decision(Squad* enemies, Action* &turn) = 0;
    int try_make_leader();
    int try_make_mass_leader();
    int get_morale() { return _morale; }
    int get_in_pack_id() { return _in_pack_id; }
    void set_in_pack_id(int value) { _in_pack_id = value; }
    int* get_damage();
    int get_range() { return _distance; }
    int get_defense() { return _defense; }
    int count_damage();
    bool make_hit_roll(int distance);
    int get_loot_list() { return _loot_list; }
    bool get_is_leader() { return _is_leader; }
    bool get_is_mass_leader() { return _is_mass_leader; }
	int what(std::string &out); 
	int get_pic_name(std::string &out);
  protected:
  	int* _damage;
  	int _distance;
  	int _defense;
    int _morale;
    int _in_pack_id;
    int _loot_list;
    bool _is_leader;
    bool _is_mass_leader;
    unsigned char* _faction;
    unsigned char* _role;
    
    int look_around(Squad* enemies, int& closest_enemy_id, int& weakest_enemy_id);
    int get_closest(int& enemy_id, Squad* enemies);
    int get_weakest(int& enemy_id, Squad* enemies);
    virtual int evaluate(int& points, Squad* enemies, int id);
    int get_distance(int to_x, int &result);
};

#endif
