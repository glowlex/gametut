#include "gcl_rpg.h"
#include <ctime>
#include <cmath>
#include <cstdlib>

gcl_rpg::Quest::Quest()
{
	level = FREE_INDEX;
}

gcl_rpg::Quest::Quest(int lvl)
{
	level = FREE_INDEX;
	level = lvl;
}

gcl_rpg::Quest::~Quest()
{
	level = FREE_INDEX;
}

int gcl_rpg::Quest::get_level()
{
	return level;
}

int gcl_rpg::Quest::get_location()
{
	return location_id;
}

bool gcl_rpg::Quest::get_completed()
{
	return is_completed;
}

void gcl_rpg::Quest::set_level(int value)
{
	level = value;
}

void gcl_rpg::Quest::set_location_id(int value)
{
	location_id = value;
}

void gcl_rpg::Quest::set_completed(bool value)
{
	is_completed = value;
}



