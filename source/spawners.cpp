#include "spawners.h"

void spawners::copy_item(TItemIgData *from, TItemIgData *to)
{
	to->name = from->name;
	to->cost = from->cost;
	to->def = from->def;
	to->ifstack = from->ifstack;
	to->usable = from->usable;
	to->kind = from->kind;
	to->disposable = from->disposable;
	to->dist = from->dist;
	to->lvlreq = from->lvlreq;
	to->manufacturer = from->manufacturer;
	for (int i = 0; i < database::STATS_COUNT; ++i)
	{
		to->statreq[i] = from->statreq[i];
		to->statbons[i] = from->statbons[i];
	}
	to->stack = from->stack;
	to->ifstack = from->ifstack;
	to->ntbons = from->ntbons;
	to->hpbons = from->hpbons;
	to->description = from->description;
	to->rarity = from->rarity;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->durability[i] = from->durability[i];
		to->dmg[i] = from->dmg[i];
	}
	for (int i = ES_HEAD; i < ES_SIZE; ++i)
	{
		to->slots[i] = from->slots[i];
	}
}

void spawners::swap_item(TItemIgData *from, TItemIgData *to)
{
	TItemIgData buf;
	copy_item(to, &buf);
	copy_item(from, to);
	copy_item(&buf, from);
}

void spawners::clear_item(TItemIgData *item)
{
	//очистка бонусов и требований к характеристикам
	for (int i = 0; i < database::STATS_COUNT; ++i)
	{
		item->statbons[i] = FREE_INDEX;
		item->statreq[i] = FREE_INDEX;
	}
	item->lvlreq = FREE_INDEX; //очиста требований к уровню
	item->hpbons = FREE_INDEX; //очистка восполняемого ХП
	item->ntbons = FREE_INDEX; //очистка восполняемой сытости
	item->dist = FREE_INDEX;   //очистка дальнобойности
	item->kind = TEquipmentKind(FREE_INDEX);   //очистка очистка вида предмета
	item->name = FREE_INDEX;   //очистка названия
	item->description = FREE_INDEX; //очистка описания
	item->manufacturer = FREE_INDEX; //очистка индекса производителя
	item->stack = FREE_INDEX; //очистка максимального стака
	item->ifstack = false; //очистка стакаемости предмета
	item->cost = FREE_INDEX; //очистка цены
	item->rarity = IR_TRASH; //очистка редкости
	item->def = FREE_INDEX; //очистка защиты
	item->dmg[0] = FREE_INDEX; //очистка мин-> урона
	item->dmg[1] = FREE_INDEX; //очистка макс-> урона
	item->durability[0] = FREE_INDEX; //очистка текущей прочности
	item->durability[1] = FREE_INDEX; //очистка макс-> прочности
									  //разрешаем помещение предмета в люой слот инвентаря
	for (int i = 0;i < ES_SIZE; ++i)
	{
		item->slots[i] = true;
	}
	item->disposable = false; //удаляем флаг расходника
	item->usable = false; //делаем предмет неиспользуемым
}

void spawners::copy_mob_data(TMobIgData *from, TMobIgData *to)
{
	to->faction = from->faction;
	to->def = from->def;
	to->level = from->level;
	to->role = from->role;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->dmg[i] = from->dmg[i];
		to->hp[i] = from->hp[i];
	}
	to->loot = from->loot;
	to->ini = from->ini;
	to->is_leader = from->is_leader;
	to->is_mass_leader = from->is_mass_leader;
}

void spawners::swap_mob_data(TMobIgData *from, TMobIgData *to)
{
	TMobIgData buf;
	copy_mob_data(to, &buf);
	copy_mob_data(from, to);
	copy_mob_data(&buf, from);
}

void spawners::clear_mob_data(TMobIgData *data)
{
	data->faction = FREE_INDEX;

	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		data->hp[i] = FREE_INDEX;
		data->dmg[i] = FREE_INDEX;
	}
	data->def = FREE_INDEX;
	data->role = database::NR_NONDEF;
	data->loot = FREE_INDEX;
	data->ini = FREE_INDEX;
}


spawners::TMobIgData spawners::Mob::spawn(TMobIgData *inp_data)
{
	TMobIgData mob_data;
	copy_mob_data(inp_data, &mob_data);
	return mob_data;
}

spawners::TMobIgData spawners::Mob::spawn(database::TMobStData *inp_data)
{
	TMobIgData mob_data;
	clear_mob_data(&mob_data);
	mob_data.ini = inp_data->ini;
	mob_data.def = inp_data->def;
	mob_data.faction = inp_data->faction;
	mob_data.loot = inp_data->loot;
	mob_data.level = START_LEVEL;
	mob_data.hp[1] = inp_data->hp;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		mob_data.dmg[i] = inp_data->dmg[i];
	}
	{
		srand(static_cast<unsigned int>(time(0)));
		for (int i = NR_GRUNT; i < NR_SIZE; ++i)
		{
			int rnd = rand() % PERCENT_MOD_CAP;
			if (inp_data->roles[i])
			{
				switch (i)
				{
				case NR_GRUNT:
				{
					if (rnd <= BASE_TANK_PROB)
					{
						mob_data.role = NR_GRUNT;
					}
					break;
				}
				case NR_DMG:
				{
					if (rnd <= BASE_DAMAGER_PROB)
					{
						mob_data.role = NR_DMG;
					}
					break;
				}
				case NR_SUPPORT:
				{
					if (rnd <= BASE_SUPPORT_PROB)
					{
						mob_data.role = NR_SUPPORT;
					}
					break;
				}
				}
			}
			if (mob_data.role != NR_NONDEF)
			{
				break;
			}
		}
	}
	switch (mob_data.role)
	{
	case NR_NONDEF:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * NONDEF_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def*NONDEF_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * NONDEF_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * NONDEF_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_GRUNT:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * GRUNT_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * GRUNT_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * GRUNT_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * GRUNT_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_DMG:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * DAMAGER_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * DAMAGER_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * DAMAGER_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * DAMAGER_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_SUPPORT:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * SUPPORT_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * SUPPORT_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * SUPPORT_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * SUPPORT_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	}
	return mob_data;
}

spawners::TMobIgData spawners::Mob::spawn(database::TMobStData *inp_data, int low_level_cap, int high_level_cap)
{
	TMobIgData mob_data;
	clear_mob_data(&mob_data);
	mob_data.ini = inp_data->ini;
	mob_data.def = inp_data->def;
	mob_data.faction = inp_data->faction;
	mob_data.loot = inp_data->loot;
	mob_data.level = START_LEVEL;
	mob_data.hp[1] = inp_data->hp;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		mob_data.dmg[i] = inp_data->dmg[i];
	}
	srand(static_cast<unsigned int>(time(0)));
	int rnd = rand() % (high_level_cap - low_level_cap) + low_level_cap;
	mob_data.level = rnd;
	if (mob_data.level > START_LEVEL)
	{
		for (int i = 0; i < (mob_data.level - START_LEVEL); ++i)
		{
			double tmp_hp, tmp_dmg, tmp_def;
			tmp_hp = mob_data.hp[1] * (1.0 + HP_CAP_RAISE);
			mob_data.hp[1] = round(tmp_hp);
			tmp_dmg = mob_data.dmg[0] * (1.0 + MOB_DMG_RAISE);
			mob_data.dmg[0] = round(tmp_dmg);
			tmp_dmg = mob_data.dmg[1] * (1.0 + MOB_DMG_RAISE);
			mob_data.dmg[1] = round(tmp_dmg);
			tmp_def = mob_data.def*(1.0 + MOB_DEF_RAISE);
			mob_data.def = round(tmp_def);
		}
		mob_data.hp[0] = mob_data.hp[1];
	}
	{
		srand(static_cast<unsigned int>(time(0)));
		for (int i = NR_GRUNT; i < NR_SIZE; ++i)
		{
			int rnd = rand() % PERCENT_MOD_CAP;
			if (inp_data->roles[i] == true)
			{
				switch (i)
				{
				case NR_GRUNT:
				{
					if (rnd <= BASE_TANK_PROB)
					{
						mob_data.role = NR_GRUNT;
					}
					break;
				}
				case NR_DMG:
				{
					if (rnd <= BASE_DAMAGER_PROB)
					{
						mob_data.role = NR_DMG;
					}
					break;
				}
				case NR_SUPPORT:
				{
					if (rnd <= BASE_SUPPORT_PROB)
					{
						mob_data.role = NR_SUPPORT;
					}
					break;
				}
				}
			}
			if (mob_data.role != NR_NONDEF)
			{
				break;
			}
		}
	}
	switch (mob_data.role)
	{
	case NR_NONDEF:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * NONDEF_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def*NONDEF_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * NONDEF_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * NONDEF_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_GRUNT:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * GRUNT_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * GRUNT_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * GRUNT_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * GRUNT_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_DMG:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * DAMAGER_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * DAMAGER_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * DAMAGER_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * DAMAGER_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	case NR_SUPPORT:
	{
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data.hp[1] * SUPPORT_HP_MODIFIER;
		mob_data.hp[1] = round(tmp_hp);
		mob_data.hp[0] = mob_data.hp[1];
		tmp_def = mob_data.def * SUPPORT_DEF_MODIFIER;
		mob_data.def = round(tmp_def);
		tmp_dmg = mob_data.dmg[0] * SUPPORT_DMG_MODIFIER;
		mob_data.dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data.dmg[1] * SUPPORT_DMG_MODIFIER;
		mob_data.dmg[1] = round(tmp_dmg);
		break;
	}
	}
	return mob_data;
}

void spawners::Mob::Check_Leadership(TMobIgData *mob_data, bool already_have_a_leader, bool already_have_a_mass_leader)
{
	srand(static_cast<unsigned int>(time(0)));
	int rnd = rand();
	rnd %= PERCENT_MOD_CAP;
	if ((!already_have_a_leader) && (rnd <= BASE_LEADER_PROB))
	{
		mob_data->is_leader = true;
		already_have_a_leader = true;
		double tmp_hp, tmp_dmg, tmp_def;
		tmp_hp = mob_data->hp[1] * LEADER_HP_MODIFIER;
		mob_data->hp[1] = round(tmp_hp);
		mob_data->hp[0] = mob_data->hp[1];
		tmp_def = mob_data->def * LEADER_DEF_MODIFIER;
		mob_data->def = round(tmp_def);
		tmp_dmg = mob_data->dmg[0] * LEADER_DMG_MODIFIER;
		mob_data->dmg[0] = round(tmp_dmg);
		tmp_dmg = mob_data->dmg[1] * LEADER_DMG_MODIFIER;
		mob_data->dmg[1] = round(tmp_dmg);
		//???????? ?? ??, ???????? ?? ????? ????-???????
		if (!already_have_a_mass_leader)
		{
			int rnd = rand();
			rnd %= PERCENT_MOD_CAP;
			if (rnd <= BASE_MASS_LEADER_PROB)
			{
				mob_data->is_mass_leader = true;
				already_have_a_mass_leader = true;
				double tmp_hp, tmp_dmg, tmp_def;
				tmp_hp = mob_data->hp[1] * MASS_LEADER_HP_MODIFIER;
				mob_data->hp[1] = round(tmp_hp);
				mob_data->hp[0] = mob_data->hp[1];
				tmp_def = mob_data->def * MASS_LEADER_DEF_MODIFIER;
				mob_data->def = round(tmp_def);
				tmp_dmg = mob_data->dmg[0] * MASS_LEADER_DMG_MODIFIER;
				mob_data->dmg[0] = round(tmp_dmg);
				tmp_dmg = mob_data->dmg[1] * MASS_LEADER_DMG_MODIFIER;
				mob_data->dmg[1] = round(tmp_dmg);
			}
		}
	}
}

spawners::TItemIgData spawners::Item::spawn(database::TItemStData *data)
{
	TItemIgData item_data;
	clear_item(&item_data);
	srand(static_cast<unsigned int>(time(0)));
	item_data.cost = data->cost;
	item_data.def = data->def;
	item_data.description = data->description;
	item_data.disposable = data->disposable;
	item_data.dist = data->dist;
	item_data.hpbons = data->hpbons;
	item_data.ifstack = data->ifstack;
	item_data.kind = data->kind;
	item_data.lvlreq = data->lvlreq;
	item_data.manufacturer = data->manufacturer;
	item_data.name = data->name;
	item_data.ntbons = data->ntbons;
	item_data.usable = data->usable;
	item_data.stack = 1;
	item_data.durability[1] = data->durability;
	item_data.durability[0] = item_data.durability[1];
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		item_data.dmg[i] = data->dmg[i];
	}
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item_data.statbons[i] = data->statbons[i];
		item_data.statreq[i] = data->statreq[i];
	}
	for (int i = 0; i < ES_SIZE; ++i)
	{
		item_data.slots[i] = data->slots[i];
	}
	//
	item_data.rarity = IR_TRASH;
	for (int i = 0; i < IR_SIZE; ++i)
	{
		int rnd = rand() % PERCENT_MOD_CAP;
		if (rnd < data->drop_rates[i])
		{
			item_data.rarity = TItemRareness(i);
		}
	}
	//
	{
		double qmod = 0.0;
		for (int i = 0; i < IR_SIZE; ++i)
		{
			if ((i >= item_data.rarity) && (item_data.rarity > IR_TRASH))
			{
				qmod += QUALITY_MODIFIER;
			}
			else
			{
				qmod -= QUALITY_MODIFIER;
			}
		}
		double tmp = item_data.cost;
		tmp *= (1.0 + qmod);
		item_data.cost = round(tmp);
		tmp = item_data.def;
		tmp *= (1.0 + qmod);
		item_data.def = round(tmp);
		for (int i = 0; i < STATS_COUNT; ++i)
		{
			tmp = item_data.statbons[i];
			tmp *= (1.0 + qmod);
			item_data.statbons[i] = round(tmp);
		}
		for (int i = 0; i < PAIR_ARR_SIZE; ++i)
		{
			tmp = item_data.dmg[i];
			tmp *= (1.0 + qmod);
			item_data.dmg[i] = round(tmp);
		}
	}
	return item_data;
}

spawners::TItemIgData spawners::Item::spawn(database::TItemStData *data, int llc, int hlc)
{
	TItemIgData item_data;
	clear_item(&item_data);
	srand(static_cast<unsigned int>(time(0)));
	item_data.cost = data->cost;
	item_data.def = data->def;
	item_data.description = data->description;
	item_data.disposable = data->disposable;
	item_data.dist = data->dist;
	item_data.hpbons = data->hpbons;
	item_data.ifstack = data->ifstack;
	item_data.kind = data->kind;
	item_data.lvlreq = rand() % (hlc - llc) + llc;
	item_data.manufacturer = data->manufacturer;
	item_data.name = data->name;
	item_data.ntbons = data->ntbons;
	item_data.usable = data->usable;
	item_data.stack = 1;
	item_data.durability[1] = data->durability;
	item_data.durability[0] = item_data.durability[1];
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		item_data.dmg[i] = data->dmg[i];
	}
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item_data.statbons[i] = data->statbons[i];
		item_data.statreq[i] = data->statreq[i];
	}
	for (int i = 0; i < ES_SIZE; ++i)
	{
		item_data.slots[i] = data->slots[i];
	}
	//
	item_data.rarity = IR_TRASH;
	for (int i = 0; i < IR_SIZE; ++i)
	{
		int rnd = rand() % PERCENT_MOD_CAP;
		if (rnd < data->drop_rates[i])
		{
			item_data.rarity = TItemRareness(i);
		}
	}
	if (item_data.lvlreq > START_LEVEL)
	{
		double tmp;
		for (int i = 0; i < (item_data.lvlreq - 1); ++i)
		{
			tmp = item_data.cost;
			tmp *= (1.0 + COST_MODIFIER);
			item_data.cost = round(tmp);
			tmp = item_data.def;
			tmp *= (1.0 + DAMDEF_MODIFIER);
			item_data.def = round(tmp);
			for (int j = 0; j < PAIR_ARR_SIZE; ++j)
			{
				tmp = item_data.dmg[j];
				tmp *= (1.0 + DAMDEF_MODIFIER);
				item_data.dmg[j] = round(tmp);
			}
			for (int j = 0; j < STATS_COUNT; ++j)
			{
				tmp = item_data.statbons[j];
				tmp *= (1.0 + STAT_MODIFER);
				item_data.statbons[j] = round(tmp);
			}
		}
	}
	{
		double qmod = 0.0;
		for (int i = 0; i < IR_SIZE; ++i)
		{
			if ((i >= item_data.rarity) && (item_data.rarity > IR_TRASH))
			{
				qmod += QUALITY_MODIFIER;
			}
			else
			{
				qmod -= QUALITY_MODIFIER;
			}
		}
		double tmp = item_data.cost;
		tmp *= (1.0 + qmod);
		item_data.cost = round(tmp);
		tmp = item_data.def;
		tmp *= (1.0 + qmod);
		item_data.def = round(tmp);
		for (int i = 0; i < STATS_COUNT; ++i)
		{
			tmp = item_data.statbons[i];
			tmp *= (1.0 + qmod);
			item_data.statbons[i] = round(tmp);
		}
		for (int i = 0; i < PAIR_ARR_SIZE; ++i)
		{
			tmp = item_data.dmg[i];
			tmp *= (1.0 + qmod);
			item_data.dmg[i] = round(tmp);
		}
	}
	return item_data;
}
