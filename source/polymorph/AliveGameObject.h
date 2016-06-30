#ifndef ALIVEGAMEOBJECT_H
#define ALIVEGAMEOBJECT_H

#include <ctime>
#include<cstdlib>
#include<cmath>

#include "GameObject.h"
#include "prototypes.h"

#pragma once

  class AliveGameObject: public GameObject {
    public:
      AliveGameObject();
      virtual ~AliveGameObject();
      int* get_health();
      int set_health(int change);
      int* get_exp();
      int get_initiative() { return _initiative; }
      int* get_coords();
      int get_coord(int index);
      int set_coords(int* value);
      int set_coord(int value, int index);
      int change_coords(int* value);
      int change_coord(int value, int index);
      int reset_coords();
      virtual bool get_is_leader() { return false; }
      virtual bool get_is_mass_leader() { return false; }
      virtual int try_make_leader() { return 0; }
      virtual int try_make_mass_leader() { return 0; }
      virtual int get_salary() { return 0; }
      virtual int get_loot_list() { return 0; }
      virtual int get_defense() = 0;
      virtual int count_damage() = 0;
      virtual int get_range() = 0;
      virtual int count_extra_damage(int basic_damage);
      virtual bool make_hit_roll(int distance) = 0;
    protected:
      int* _health;
      int* _exp;
      int _initiative;
      int* _coords;
  };

#endif
