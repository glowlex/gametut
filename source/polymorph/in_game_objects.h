#pragma once

#ifndef INGAMEOBJECTS_H
#define INGAMEOBJECTS_H

namespace generic_consts {
	
  const int SILENCE_CODE = 0;
  const int BATTLE_CODE = 1;

  const int EMPTY_STACK = 0;
  
  const int FREE_INDEX = -1;
  const int CURRENT_VALUE_INDEX = 0;
  const int MAXIMAL_VALUE_INDEX = 1;
  
  const int PLAYER_SQUAD_ID = 0;
  
  const int PLAYER_SQUAD_SIZE = 5;
  const int MONSTER_SQUAD_SIZE =  10;
  const int MAX_MONSTER_SQUADS = 5;

  const int MIN_COLLECTABLE_STACK = 1;
  const int MAX_COLLECTABLE_STACK = 200;

  const int MIN_CONSUMABLE_STACK = 1;
  const int MAX_CONSUMABLE_STACK = 200;
  
  const int MAX_MORALE_VALUE = 100;

  const int OK_CODE = 0;
  const int SOME_ERROR_CODE = 1;
  
  const int TRADERS_COUNT = 4;
  const int MAX_MERCENARIES = 8;
  
  const int LOCAL_MAP_WIDTH = 64;
  const int LOCAL_MAP_HEIGHT = 64;
  const int LOCAL_MAP_STEP = 8;
  const int LOCAL_MASKS_COUNT = 26;
  
  const int GLOBAL_MAP_WIDTH = 320;
  const int GLOBAL_MAP_HEIGHT = 320;
  const int GLOBAL_MAP_STEP = 32;
  const int GLOBAL_MASKS_COUNT = 26;
  
  const int MAX_LOCAL_TEXTURES_COUNT = 4;
  const int MAX_GLOBAL_TEXTURES_COUNT = 10;

  const int START_LEVEL = 1;
  const int MAX_LEVEL = 70;
  const int LEVEL_RANGE = 3;
  
  const int FIRST_LEVELUP_CAP = 100;
  
  const int ACTIONS_PER_TURN = 2;
  
  const int STAT_UP_PER_LEVEL = 2;
  const int HIT_POINTS_RAISE_PER_LEVEL = 10;
  const int POINTS_PER_LEVEL = 5;
  
  const int BASIC_SPEED = 5;
  const int BASIC_SIGHT_DISTANCE = 40;

  const int NAMESTRING_SIZE = 31;
  const int DESCRSTRING_SIZE = 301;
  
  const double MANUFACTURER_BONUS = 1.15;
  
  const int FACTIONS_COUNT = 5;
  
  const int BASE_CRITICAL_HIT_CHANCE = 30;
  const int CRITICAL_DAMAGE_MODIFIER = 2;
  
  const int ONE_SHOT_MODIFIER = 20;
  const int ONE_STEP_MODIFIER = 15;
  const int CLOSEST_UNIT = 20;
  const int WEAKEST_UNIT = 26;
  
  const int PERCENT_CAP = 100;
  const int PERCENT_MOD_CAP = 100;
  
  const int SPAWN_CHANCE_DECREMENT = 10;
  
  const char* NAME_TAG = "$N";
  const char* STATS_TAG = "$S";
  const char* REQS_TAG = "$R";
  const char* BONS_TAG = "$B";
  const char* DAMDEF_TAG = "$D";
  const char* LEVEL_TAG = "$L";
  const char* COST_TAG = "$C";
  const char* DESCR_TEXT_TAG = "$T";
  const char* QUALITY_TAG = "$Q";
  const char* HEALTH_TAG = "$H";
  const char* OTHER_TAG = "$O";
  const char* KIND_TAG = "$K";

  enum TCharStats { CS_ACCURACY, CS_REACTION, CS_STRENGTH, CS_TOUGHNESS, CS_AWARENESS, CS_INTELLIGENCE, CS_PERSUASION, CS_SPEED, CS_SIZE };
  enum TEquipmentSlot { ES_HEAD, ES_CHEST, ES_HANDS, ES_BOOTS, ES_LEGS, ES_TRINKET1, ES_TRINKET2, ES_TRINKET3, ES_TRINKET4, ES_WEAPON1, ES_WEAPON2, ES_SIZE };
  enum TEquipmentKind { EK_PISTOL, EK_SMG, EK_ASSAULT_RIFLE, EK_SNIPER_RIFLE, EK_MELEE, EK_LIGHT, EK_MEDIUM, EK_HEAVY, EK_TRINKET, EK_SIZE};
  enum TActionIds { AD_ATTACK, AD_MOVE, AD_SIZE };

}

#endif
