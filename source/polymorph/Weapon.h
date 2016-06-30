#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include "EquipableItem.h"
#include "prototypes.h"

#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace generic_consts;
using namespace prototypes;


  class Weapon: public EquipableItem {
    public:
      Weapon();
      Weapon(TEquipablePrototype &prototype, unsigned char* name, unsigned char* manufacturer, int level);
      virtual ~Weapon();
      int* get_damage();
      int get_distance() { return _distance; }
      bool get_one_handed();
      TEquipmentKind get_kind();
      int what(std::string &out);
      int get_pic_name(std::string &out);
    protected:
    	int* _damage;
    	int _distance;
    	bool _one_handed;
    	TEquipmentKind _kind;
  };

#endif
