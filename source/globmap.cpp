#include "globmap.h"

void globmap::copy_location_data(struct TLocationIgData *from, struct TLocationIgData *to)
{
  for (int j = 0; j < PAIR_ARR_SIZE; ++j)
  {
    for (int i = 0; i < MAX_PACKS_COUNT; ++i)
    {
      to->combat_probs[i][j] = from->combat_probs[i][j];
	}
	to->levels[j] = from->levels[j];
  }
  for (int i = 0; i < TK_SIZE; ++i)
  {
  	to->trader_probs[i] = from->trader_probs[i];
  }
  to->has_been = from->has_been;
}

void globmap::swap_location_data(TLocationIgData *from,  TLocationIgData *to)
{
  TLocationIgData buf;
  copy_location_data(to, &buf);
  copy_location_data(from, to);
  copy_location_data(&buf, from);
}

void globmap::clear_location_data(TLocationIgData *data)
{
  for (int j = 0; j < PAIR_ARR_SIZE; ++j)
  {
  	for (int i = 0; i < MAX_PACKS_COUNT; ++i)
  	{
  	  data->combat_probs[i][j] = FREE_INDEX;
    }
    data->levels[j] = FREE_INDEX;
  }
  for (int i = 0; i < TK_SIZE; ++i)
  {
  	data->trader_probs[i] = FREE_INDEX;
  }
  data->has_been = false;
}

globmap::TLocationIgData globmap::Location::generate(database::TLocationStData *tmp, player::Player *pl)
{
  srand(static_cast<unsigned int>(time(0)));
  TLocationIgData res;
  clear_location_data(&res);
  for(int j = 0; j < PAIR_ARR_SIZE; ++j)
  {
    for (int i = 0; i < MAX_PACKS_COUNT; ++i)
    {
      res.combat_probs[i][j] = tmp->combat_probs[i][j];
	}
	int rnd = rand();
	res.levels[j] = rnd % LOCATION_LEVEL_SEED - (LOCATION_LEVEL_SEED / 2);
	res.levels[j] += pl->get_level();
  }
  if (res.levels[0]>res.levels[1])
  {
    int buf = res.levels[1];
    res.levels[1] = res.levels[0];
    res.levels[0] = buf;
  }
  for (int i = 0; i < TK_SIZE; ++i)
  {
    res.trader_probs[i] = tmp->trader_probs[i];
  }
  return res;
}

//TO-DO: rethink and rewrite
bool globmap::Location::on_enter(TLocationIgData *curr_loc)
{
  if (!curr_loc->has_been)
  {
  	curr_loc->has_been = true;
  }
}

globmap::GlobalMap::GlobalMap()
{
  player_position = FREE_INDEX;
  for (int i = 0; i < GLOBAL_MAP_SIZE; ++i)
  {
  	clear_location_data(&(map[i]));
  }
}

globmap::GlobalMap::GlobalMap(TLocationIgData *inp_map, int map_sz, short plr_pos)
{
  if (map_sz >= GLOBAL_MAP_SIZE)
  {
    for (int i = 0; i < GLOBAL_MAP_SIZE; ++i)
    {
      copy_location_data(&(inp_map[i], &(map[i])));
	}
  }
  else
  {
    for (int i = 0; i < map_sz; ++i)
    {
      copy_location_data(&(inp_map[i], &(map[i])));
	}
	for (int i = map_sz; i < GLOBAL_MAP_SIZE; ++i)
	{
      clear_location_data(&(map[i]));
	}
  }
  player_position = plr_pos;
}

globmap::GlobalMap::~GlobalMap()
{
}

short globmap::GlobalMap::get_player_position()
{
  return player_position;
}

void globmap::GlobalMap::set_player_position(short value)
{
  player_position = value;
}

globmap::TLocationIgData globmap::GlobalMap::get_location(int ind)
{
  return map[ind];
}

void globmap::GlobalMap::set_location(TLocationIgData *inp_loc, int inp_sz, int start_ind)
{
  if ((start_ind > 0) && (start_ind < GLOBAL_MAP_SIZE))
  {
    if (inp_sz >= (GLOBAL_MAP_SIZE - start_ind))
    {
      for (int i = start_ind; i < GLOBAL_MAP_SIZE; ++i)
      {
        copy_location_data(&(inp_loc[i - start_ind]), &(map[i]));
	  }
    }
    else
    {
      for (int i = start_ind; i < inp_sz; ++i)
      {
        copy_location_data(&(inp_loc[i - start_ind]),&(map[i]));
	  }
	}
  }
}
