#pragma once

#ifndef EQUIPABLEITEM_H
#define EQUIPABLEITEM_H

#include "UsableItem.h"
#include "PartyMember.h"
#include <cstdlib>
#include <cmath>

using namespace generic_consts;
using namespace prototypes;

  class EquipableItem: public UsableItem {
    public:
      EquipableItem();
      virtual ~EquipableItem();
      int* get_stat_reqs();
      int* get_stat_bons();
      char* get_manufacturer_id();
      int* get_slots();
      int use(AliveGameObject* user); 
      virtual int get_distance() { return 0; }
      virtual int get_defense() { return 0; }
      virtual int* get_damage() { return NULL; }
      
    protected:
	
	  bool meets_stat_reqs(AliveGameObject* &user);
	        	
      int* _stat_reqs;
      int* _stat_bons;
      bool _in_bag;
      unsigned char* _manufacturer_id;
      int* _slots;
  };

#endif
