#include "database.h"

void database::copy_loot(struct TLoot *from, struct TLoot *to)
{
	to->id = from->id;               //копирование идентификатора предмета
	to->max_quant = from->max_quant; //копирование максимально дропаемого количества предметов
	to->poss = from->poss;           //копирование вероятности дропа
}

void database::swap_loot(struct TLoot *from, struct TLoot *to)
{
	TLoot buf;
	copy_loot(to, &buf);
	copy_loot(from, to);
	copy_loot(&buf, from);
}

void database::clear_loot(struct TLoot *data)
{
	data->id = FREE_INDEX;        //очистка идентификатора предмета
	data->max_quant = FREE_INDEX; //очистка максимально дропаемого количества предметов
	data->poss = FREE_INDEX;      //очистка вероятности дропа
}

void database::copy_loot_list(struct TLootList *from, struct TLootList *to)
{
	to->cash = from->cash; //копирование денег
	to->exp = from->exp;   //копирование опыта
	for (int i = 0; i < LOOT_LIST_SIZE; ++i)
	{
		copy_loot(&(to->loot[i]), &(from->loot[i])); //копирование элементов лут-листа
	}
}

void database::swap_loot_list(struct TLootList *from, struct TLootList *to)
{
	TLootList buf;
	copy_loot_list(to, &buf);
	copy_loot_list(from, to);
	copy_loot_list(&buf, from);
}

void database::clear_loot_list(struct TLootList *data)
{
	data->cash = FREE_INDEX; //обнуление денег
	data->exp = FREE_INDEX;  //обнуление опыта
	for (int i = 0; i < LOOT_LIST_SIZE; ++i)
	{
		clear_loot(&(data->loot[i])); //очистка лут-листа
	}
}

void database::copy_item(struct TItemStData *from, struct TItemStData *to)
{
	to->name = from->name;
	to->imgname = from->imgname;
	to->cost = from->cost;
	to->def = from->def;
	to->ifstack = from->ifstack;
	to->usable = from->usable;
	to->kind = from->kind;
	to->disposable = from->disposable;
	to->dist = from->dist;
	to->lvlreq = from->lvlreq;
	to->manufacturer = from->manufacturer;
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		to->statreq[i] = from->statreq[i];
		to->statbons[i] = from->statbons[i];
	}
	to->ifstack = from->ifstack;
	to->ntbons = from->ntbons;
	to->hpbons = from->hpbons;
	to->description = from->description;
	to->imgname = from->imgname;
	to->durability = from->durability;
	to->quest = from->quest;
	for (int i = IR_TRASH; i < IR_SIZE; ++i)
	{
		to->drop_rates[i] = from->drop_rates[i];
	}
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->dmg[i] = from->dmg[i];
	}
	for (int i = ES_HEAD; i < ES_SIZE; ++i)
	{
		to->slots[i] = from->slots[i];
	}
}

void database::swap_item(TItemStData *from, TItemStData *to)
{
	TItemStData buf;
	copy_item(to, &buf);
	copy_item(from, to);
	copy_item(&buf, from);
}

void database::clear_item(TItemStData *item)
{
	//обнуление значений полей требований и бонусов к характеристикам носителя
	for (int i = 0; i < STATS_COUNT; ++i)
	{
		item->statbons[i] = FREE_INDEX;
		item->statreq[i] = FREE_INDEX;
	}
	item->lvlreq = FREE_INDEX; //обнуления требований к уровню носителя
	item->hpbons = FREE_INDEX; //обнуление исцеления при использовании предмета
	item->ntbons = FREE_INDEX; //обнуление восполнения сытости при использовании предмета
	item->dist = FREE_INDEX; //обнуление дальнобойности предмета
	item->kind = TEquipmentKind(FREE_INDEX); //установка неизвестного типа предмета
	item->name = FREE_INDEX; //обнуление названия предмета
	item->description = FREE_INDEX; //очистка описания предмета
	item->manufacturer = FREE_INDEX; //очистка данных  о производителе
	item->ifstack = false; //считать предмет нескладываемым в стопки
	item->cost = FREE_INDEX; //обнуление стоимости предмета
	//чистка шансов выпадения предмета по всем уровням редкости
	for (int i = 0; i < IR_SIZE; ++i)
	{
		item->drop_rates[i] = FREE_INDEX;
	}
	item->def = FREE_INDEX; //обнуление уровня защиты предмета
	item->dmg[0] = FREE_INDEX; //обнуление мин->наносимого урона при атаке
	item->dmg[1] = FREE_INDEX; //обнуление макс-> наносимого урона при атаке
	item->durability = FREE_INDEX; //обнуление прочности предмета
	//запрет на экипировку шаблона в любой слот инвентаря
	for (int i = 0;i < ES_SIZE; ++i)
	{
		item->slots[i] = true;
	}
	item->disposable = false; //считать предмет нерасходуемым
	item->usable = false; //считать предмет неиспользуемым
	item->imgname = FREE_INDEX; //очистка имени файла иконки
	item->quest = FREE_INDEX; //очистка связей шаблона с квестами
}

void database::copy_mob_data(TMobStData *from, struct TMobStData *to)
{
	to->faction = from->faction; //копирование фракции шаблона
	to->hp = from->hp; //копирование ХП шаблона
	to->def = from->def; //копирование защиты шаблона
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		to->dmg[i] = from->dmg[i]; //копирование информации о наносимом уроне
	}
	for (int i = 0; i < NR_SIZE; ++i)
	{
		to->roles[i] = from->roles[i]; //копирование информации о доступности ролевых моделей
	}
	to->loot = from->loot; //копирование лут-листа
	to->dp = from->dp;
	to->ini = from->ini;
}

void database::swap_mob_data(struct TMobStData *from, struct TMobStData *to)
{
	TMobStData buf;
	copy_mob_data(to, &buf);
	copy_mob_data(from, to);
	copy_mob_data(&buf, from);
}

void database::clear_mob_data(struct TMobStData *data)
{
	data->faction = FREE_INDEX;
	data->hp = FREE_INDEX;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		data->dmg[i] = FREE_INDEX; //
	}
	data->def = FREE_INDEX; //
	for (int i = 0; i < NR_SIZE; ++i)
	{
		data->roles[i] = false; //
	}
	data->loot = FREE_INDEX; //
	data->dp = FREE_INDEX; //
	data->ini = FREE_INDEX;
}

void database::copy_location_data(TLocationStData *from, TLocationStData *to)
{
  for (int j = 0; j < PAIR_ARR_SIZE; ++j)
  {
    for (int i = 0; i < MAX_PACKS_COUNT; ++i)
    {
      to->combat_probs[i][j] = from->combat_probs[i][j];
    }
  }
  for (int i = 0; i < TK_SIZE; ++i)
  {
  	to->trader_probs[i] = from->trader_probs[i];
  }
}

void database::swap_location_data(TLocationStData *from, TLocationStData *to)
{
  TLocationStData buf;
  copy_location_data(to, &buf);
  copy_location_data(from, to);
  copy_location_data(&buf, from);
}

void database::clear_location_data(TLocationStData *data)
{
  for (int j = 0; j < PAIR_ARR_SIZE; ++j)
  {
    for (int i = 0; i < MAX_PACKS_COUNT; ++i)
    {
      data->combat_probs[i][j] = FREE_INDEX;
	}
  }
  for (int i = 0; i < TK_SIZE; ++i)
  {
    data->trader_probs[i] = FREE_INDEX;
  }
}

void database::copy_ability_data(TAbilityData *from, TAbilityData *to)
{
	to->name = from->name;
	to->description = from->description;
	to->tgt_number = from->tgt_number;
	to->area = from->area;
	to->range = from->range;
	to->duration = from->duration;
	for (int i = 0; i < PAIR_ARR_SIZE; ++i)
	{
		for (int j = 0; j < TS_SIZE; ++j)
		{
			to->effect[j][i] = from->effect[j][i];
			to->tick[j][i] = from->tick[j][i];
		}
	}
	for (int i = 0; i < AT_SIZE; ++i)
	{
		to->application[i] = from->application[i];
	}
	for (int i = 0; i < TS_SIZE; ++i)
	{
		to->affect_kind[i] = from->affect_kind[i];
	}
}

void database::swap_ability_data(struct TAbilityData *from, struct TAbilityData *to)
{
	TAbilityData buf;
	copy_ability_data(to, &buf);
	copy_ability_data(from, to);
	copy_ability_data(&buf, from);
}

void database::clear_ability_data(struct TAbilityData *data)
{
	data->name.clear();
	data->description.clear();
	data->tgt_number = FREE_INDEX;
	data->area = FREE_INDEX;
	data->range = FREE_INDEX;
	data->duration = FREE_INDEX;
	for (int j = 0; j < PAIR_ARR_SIZE; ++j)
	{
		for (int i = 0; i < TS_SIZE; ++i)
		{
			data->effect[i][j] = FREE_INDEX;
			data->tick[i][j] = FREE_INDEX;
		}
	}
	for (int i = 0; i < AT_SIZE; ++i)
	{
		data->application[i] = false;
	}
	for (int i = 0; i < TS_SIZE; ++i)
	{
		data->affect_kind[i] = PA_NONDEF;
	}
}

database::Database::Database()
{
	loot.clear();
	items.clear();
	mobs.clear();
}

database::Database::~Database()
{
	loot.clear();
	items.clear();
	mobs.clear();
}

database::TItemStData database::Database::get_item(int ind)
{
	if ((ind > FREE_INDEX) && (ind < items.size()))
	{
		return items[ind];
	}
}

database::TMobStData database::Database::get_mob(int ind)
{
	if ((ind > FREE_INDEX) && (ind < mobs.size()))
	{
		return mobs[ind];
	}
}

database::TLootList database::Database::get_loot_list(int ind)
{
	if ((ind > FREE_INDEX) && (ind < loot.size()))
	{
		return loot[ind];
	}
}

int database::Database::get_items_size()
{
	return items.size();
}

int database::Database::get_mobs_size()
{
	return mobs.size();
}

int database::Database::get_loot_list_size()
{
	return loot.size();
}

bool database::Database::set_item(struct TItemStData *data)
{
	bool res = false;
	if (items.size() < ITEM_STORAGE_SIZE)
	{
		items.resize(items.size() + 1);
		copy_item(data, &(items[items.size() - 1]));
		res = true;
	}
	return res;
}

bool database::Database::set_mob(TMobStData * data)
{
	bool res = false;
	if (mobs.size() < MOBS_STORAGE_SIZE)
	{
		mobs.resize(mobs.size() + 1);
		copy_mob_data(data, &(mobs[mobs.size() - 1]));
		res = true;
	}
	return res;
}

bool database::Database::set_loot_list(TLootList *data)
{
	bool res = false;
	loot.resize(loot.size() + 1);
	copy_loot_list(data, &(loot[loot.size() - 1]));
	res = true;
	return res;
}

bool database::Database::remove_item(int ind)
{
	bool res = false;
	if ((ind > FREE_INDEX) && (ind < items.size()))
	{
		items.erase(items.begin() + ind);
		res = true;
	}
	return res;
}

bool database::Database::remove_mob(int ind)
{
	bool res = false;
	if ((ind > FREE_INDEX) && (ind < mobs.size()))
	{
		mobs.erase(mobs.begin() + ind);
		res = true;
	}
	return res;
}

bool database::Database::remove_loot_list(int ind)
{
	bool res = false;
	if ((ind > FREE_INDEX) && (ind < loot.size()))
	{
		loot.erase(loot.begin() + ind);
		res = true;
	}
	return res;
}
