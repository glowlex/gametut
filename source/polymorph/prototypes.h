#pragma once

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "in_game_objects.h"

using namespace generic_consts;

namespace prototypes {

  const int PAIR_ARR_SIZE = 2;
  const int STATS_COUNT = 8;
  
  const int MERC_PRESETS_COUNT = 3;
  const int MONSTER_PRESETS_COUNT = 10;
  
  const int LOOT_LISTS_COUNT = 11;
  const int LOOTS_COUNT = 24;
  
  const int STAT_PRESETS_COUNT = 10;
  const int MERC_NAMES_COUNT = 10;
  const int EQUIPMENT_PRESETS_COUNT = 10;
  //const int MERC_PRESETS_COUNT = 10;
  
  const int START_CASH = 1000;
  
  const int MERC_FACES_COUNT = 10;
  const int MONSTER_FACES_COUNT = 10;
  const int ITEM_PIC_VARIANTS_COUNT = 3;
  
  const int LOCATION_PRESETS_COUNT = 3;
  const int PACK_INFO_COUNT = 3;
  const int PACK_QUERY_IDS_COUNT =3;
  const int TRADER_CHANCES_COUNT = 3;
  
  const int NPC_PRESETS_COUNT = 4;
  
  const int MANUFACTURERS_COUNT = 10;
  const int NAMES_COUNT = 10;
  
  const int CONSUMABLES_COUNT = 6;
  
  const int BACKPACK_SIZE = 36;
  const int STORAGE_SIZE = 72;
  const int BANK_SIZE = 154;
  const int LOOT_LIST_SIZE = 16;
  
  const int VENDOR_CAPACITY = 154;
  const int BASIC_VENDOR_CHARGE = 10;
  
  const double ITEM_RARITY_MODIFIER = 0.25;
  const double ITEM_DAMAGE_MINMAX_RATIO = 1.25;
  
  const double DAMDEF_LEVEL_MODIFIER = 1.0625;
  const double COST_LEVEL_MODIFIER = 1.03;
  const double STATS_LEVEL_MODIFIER = 1.0625;
  
  const int STAT_RAISE_PER_LEVEL = 1;
  const int DAMDEF_RAISE_PER_LEVEL = 5;
  const int HP_RAISE_PER_LEVEL = 8;
  const int COST_RAISE_PER_LEVEL = 5;
  
  const double CASH_RAISE = 1.10;
  const double EXP_RAISE = 1.10;
  
  const int BASE_TRASH_CHANCE = 30;
  const int BASE_COMMON_CHANCE = 80;
  const int BASE_GOOD_CHANCE = 25;
  const int BASE_RARE_CHANCE = 12;
  const int BASE_EPIC_CHANCE = 8;
  const int BASE_LEGENDARY_CHANCE = 3;
  
  const int BASE_NONDEF_PROB = 40;
  const int BASE_GRUNT_PROB = 30;
  const int BASE_SUPPORT_PROB = 20;
  const int BASE_DAMAGER_PROB = 50;

  const int BASE_LEADER_PROB = 10;
  const int BASE_MASS_LEADER_PROB = 20;

  const double NONDEF_HP_MODIFIER = 1.0;
  const double NONDEF_DMG_MODIFIER = 1.0;
  const double NONDEF_DEF_MODIFIER = 1.0;

  const double GRUNT_HP_MODIFIER = 1.50;
  const double GRUNT_DMG_MODIFIER = 0.50;
  const double GRUNT_DEF_MODIFIER = 2.25;

  const double SUPPORT_HP_MODIFIER = 0.75;
  const double SUPPORT_DMG_MODIFIER = 1.25;
  const double SUPPORT_DEF_MODIFIER = 0.50;

  const double DAMAGER_HP_MODIFIER = 0.50;
  const double DAMAGER_DMG_MODIFIER = 2.25;
  const double DAMAGER_DEF_MODIFIER = 0.75;
 
  const double LEADER_HP_MODIFIER = 1.50;
  const double LEADER_DMG_MODIFIER = 1.50;
  const double LEADER_DEF_MODIFIER = 1.50;
  const double LEADER_EXP_MODIFIER = 1.50;
  const double LEADER_CASH_MODIFIER = 1.50;

  const double MASS_LEADER_HP_MODIFIER = 1.25;
  const double MASS_LEADER_DMG_MODIFIER = 1.25;
  const double MASS_LEADER_DEF_MODIFIER = 1.25;
  const double MASS_LEADER_EXP_MODIFIER = 1.25;
  const double MASS_LEADER_CASH_MODIFIER = 1.25;
  
  const double NONDEF_MOVE_COST = 1.0;
  const double NONDEF_COVER_COST = 1.0;
  const double NONDEF_FLEE_COST = 1.0;
  const double NONDEF_ATTACK_COST = 1.0;
  
  const double GRUNT_MOVE_COST = 1.0;
  const double GRUNT_COVER_COST = 1.10;
  const double GRUNT_FLEE_COST = 0.25;
  const double GRUNT_ATTACK_COST = 1.25;
  
  const double DAMAGER_MOVE_COST = 1.0;
  const double DAMAGER_COVER_COST = 1.25;
  const double DAMAGER_FLEE_COST = 0.75;
  const double DAMAGER_ATTACK_COST = 1.75;
  
  const double SUPPORT_MOVE_COST = 1.0;
  const double SUPPORT_COVER_COST = 1.5;
  const double SUPPORT_FLEE_COST = 1.10;
  const double SUPPORT_ATTACK_COST = 0.8; 

//  const double MANUFACTURER_BONUS = 1.13;

  enum TItemRareness { IR_TRASH, IR_COMMON, IR_GOOD, IR_RARE, IR_EPIC, IR_LEGENDARY };

  struct TConsumablePrototype {
  	char* _name;
  	char* _description;
	int _cost;
	int _effect;  
  };

  struct TCollectablePrototype {
    char* _name;
  	char* _description;
    int _cost;
    int _id;
  };

  struct TEquipablePrototype {
  	int _name_id; // set -1 if generated in-situ
  	int _manufacturer_id; // set -1 if generated in-situ
  	unsigned char* _description;
  	unsigned char* _name;
  	unsigned char* _manufacturer;
  	int _cost;
    int _damdef;
    int _distance;
    int _stat_reqs[STATS_COUNT];
    int _stat_bons[STATS_COUNT];
    int _slots[ES_SIZE];
    int kind;
  };
  
  struct TLoot {
    int _max_quant;
    int _chance;
    int _id;
  };

  struct TLootList {
    TLoot* _loot;
    int _cash;
    int _exp;
  };
  
  struct TLootListPrototype {
    int* _loot_ids;
    int _cash;
    int _exp;
  };
  
  struct TLocationPrototype {
    int** _packs;
    int* _trader_chances;
    int _fight_chance;
  };

  struct TTilePrototype {
    int _texture;
    int _defense;
    bool _is_passable;
    unsigned char* _description;
    unsigned char* _name;
  };
  
  struct TNPCPrototype {
    int _content_id;
    int _charge; //set -1 for not traders
    unsigned char* _speech;
    unsigned char* _name;
    unsigned char* _description;
  };
  
  struct TMonsterPrototype {
  	int _name_id; // set -1 if generated in-situ
    int _faction_id; // set -1 if generated in-situ
    int _hp;
    int _damage;
    int _distance;
    int _defense;
    int _loot_list_id;
    int _decrement;
    int _initiative;
  };

  struct TPartyMemberPrototype {
    unsigned char* _name;
    bool _gender;
    int _salary;
    int _health;
    int _initiative;
    int* _stats;
    int* _equipment;
  };
}

#endif
