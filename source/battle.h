#pragma once

#include <ctime>
#include <cmath>
#include <cstdlib>

#include "gtl_rpg.h"
#include "player.h"
#include "database.h"
#include "spawners.h"

namespace battle
{
  using namespace gtl_rpg;

  const double PACK_DEBUFF_MODIFIER = 0.75;      //pack all-stat debuff when leader dies

  //=======================================================================================\\
  //<-----------------------------!AI action value modifiers!----------------------------->\\
  /*=======================================================================================*/
	
  const double NONDEF_IDLE_MOD = 1.0;
  const double NONDEF_MOVE_MOD = 1.0;
  const double NONDEF_CAST_MOD = 1.0;
  const double NONDEF_ATTACK_MOD = 1.0;
  const double NONDEF_COVER_MOD = 1.0;

  const double GRUNT_IDLE_MOD = 1.0;
  const double GRUNT_MOVE_MOD = 1.0;
  const double GRUNT_CAST_MOD = 1.0;
  const double GRUNT_ATTACK_MOD = 1.0;
  const double GRUNT_COVER_MOD = 1.0;

  const double DMG_IDLE_MOD = 1.0;
  const double DMG_MOVE_MOD = 1.0;
  const double DMG_CAST_MOD = 1.0;
  const double DMG_ATTACK_MOD = 1.0;
  const double DMG_COVER_MOD = 1.0;

  const double SUPPORT_IDLE_MOD = 1.0;
  const double SUPPORT_MOVE_MOD = 1.0;
  const double SUPPORT_CAST_MOD = 1.0;
  const double SUPPORT_ATTACK_MOD = 1.0;
  const double SUPPORT_COVER_MOD = 1.0;

  //=======================================================================================\\
  //=======================================================================================\\

  const int MAP_WIDTH = 128;
	
  enum TActionList { AL_IDLE, AL_MOVE, AL_CAST, AL_ATTACK, AL_COVER, AL_SIZE }; //availible actions per turn

  struct TAction //action data (for turn queue)
  {
    int sender_ids[PAIR_ARR_SIZE];
    int target_ids[PAIR_ARR_SIZE];
	TActionList  id;
  };

  void copy_action_data(struct TAction *from, struct TAction *to);
  void swap_action_data(struct TAction *from, struct TAction *to);
  void clear_action_data(struct TAction *data);

  class Battlefield //battle class
  {
    public:

      Battlefield();
      ~Battlefield();
      int spawn_prob(int spawned, int dp);
      int total_enemies();
      void turn_sort(player::Player *pl);
      bool pack_has_leader(int pack_id);
      bool have_mass_leader();
      void spawn_new_mob(database::Database *db, int mob_id, int pack_id, int llc, int hlc);
      void spawn_new_pack(database::Database *db, int mob_id, int llc, int hlc);
      void clear_dead(database::Database *db, int llc, int hlc);

      std::vector<std::vector<spawners::TMobIgData> > enemies; //spawned mob packs  vector

      private:

        int reward_cash;
        int reward_exp;
        std::vector<spawners::TItemIgData> loot;                //gained loot vector
        std::vector<TBuffData> buffs;                 //active buffs/dots/hots
        std::vector<int[PAIR_ARR_SIZE]> turn_order;

	};

    class AI //AI handler class
    {
      public:

        //main action selector
        static battle::TAction select(database::TNPCRole role, player::Player *pl, Battlefield *bf, int i, int j);

      private:

        //action selectors for different NPC behaviors
        static battle::TAction healer_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction damager_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction grunt_ai(player::Player *pl, Battlefield *bf, int i, int j);
        static battle::TAction nondef_ai(player::Player *pl, Battlefield *bf, int i, int j);

    };
}
