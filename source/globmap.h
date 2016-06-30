#pragma once
#include "gtl_rpg.h"
#include "battle.h"

namespace globmap
{
  using namespace gtl_rpg;

  const int LOCATION_LEVEL_SEED = 3; //half-width of level seed (for generating upper and lower level borders while spawning location)
  const int GLOBAL_MAP_SIZE = 32;    //global map size (locations count)

  struct TLocationIgData //location data (in-game generated)
  {
    int combat_probs[MAX_PACKS_COUNT][PAIR_ARR_SIZE]; //spawn chances array for different mob templates. Every location may contain up to MAX_PACKS_COUNT different mob types. first value - mob template index in database, second - pack spawn chance
    int trader_probs[TK_SIZE];                        //spawn chances array for different trader types in location
    int levels[PAIR_ARR_SIZE];                        //level difference - lower and upper borders, used for mob, items and traders store spawn
    bool has_been;                                    //flag, true if character had already been in this location
  };

  //
  void copy_location_data(struct TLocationIgData *from, struct TLocationIgData *to);
  //
  void swap_location_data(struct TLocationIgData *from, struct TLocationIgData *to);
  //
  void clear_location_data(struct TLocationIgData *data);
  
  class Location //location handler class
  {
  	public:
  	  static globmap::TLocationIgData generate(database::TLocationStData *tmp, player::Player *pl); //location generation function using database template (use for player's first visit)
  	  static bool on_enter(TLocationIgData *curr_loc);                                              //traders and mobs spawn function (use every time player enters location)
  }
  
  class GlobalMap //global map class
  {
    public:
    	
      GlobalMap();
      GlobalMap(TLocationIgData *inp_map, int map_sz, short plr_pos);
      ~GlobalMap();
      short get_player_position();
      void set_player_position(short value);
      globmap::TLocationIgData get_location(int ind);
      void set_location(TLocationIgData *inp_loc, int inp_sz, int start_ind);

    private:

      short player_position;                //index of current player's location
      TLocationIgData map[GLOBAL_MAP_SIZE]; //location list
  }
  
}
