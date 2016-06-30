#include "gtl_rpg.h"

bool gtl_rpg::is_pair_variable(int arsz, int elsz)
{
	bool res = false;
	if (arsz / elsz == PAIR_ARR_SIZE)
	{
		res = true;
	}
	return res;
}



void gtl_rpg::copy_buff_data(struct TBuffData *from, struct TBuffData to)
{
	to->from = from->from;
	to->to = from->to;
	to->is_const = from->is_const;
	to->kind = from->kind;
	to->time = from->time;
	to->eff_kind = from->eff_kind;
	for (int i = 0 i < PAIR_ARR_SIZE; ++i)
	{
		to->effect[i] = from->effect[i];
	}
}

void gtl_rpg::swap_buff_data(struct TBuffData *from, struct TBuffData *to)
{	
	TBuffData buf;
	copy_buff_data(to, &buf);
	copy_buff_data(from, to);
	copy_buff_data(&buf, from);
}

void gtl_rpg::clear_buff_data(struct TBuffData *data)
{
	data->from = FREE_INDEX;
	data->to = FREE_INDEX;
	data->eff_kind = PA_NONDEF;
	data->is_const = false;
	data->kind = FREE_INDEX;
	data->time = FREE_INDEX;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		data->effect[i] = FREE_INDEX;
	}
}

void gtl_rpg::copy_maptile_data(struct TMapTile *from, struct TMapTile *to)
{
	to->id = from->id;
	to->obj[0] = from->obj[0];
	to->obj[1] = from->obj[1];
	to->passable = from->passable;
}

void gtl_rpg::swap_maptile_data(struct TMapTile *from, struct TMapTile *to)
{
	TMapTile buf;
	copy_maptile_data(to, &buf);
	copy_maptile_data(from, to);
	copy_maptile_data(&buf, from);
}

void gtl_rpg::clear_maptile_data(struct TMapTile *data)
{
	data->id = TL_NONDEF;
	data->obj[0] = FREE_INDEX;
	data->obj[1] = FREE_INDEX;
	data->passable = false;
}

}
