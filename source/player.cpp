#include "player.h"
#include <cstdlib>


void player::copy_inventory_equipped(TInventoryData *from, TInventoryData *to)
{
  for (int i = 0; i < ES_SIZE; ++i)
  {
    spawners::copy_item(&(from->equipped[i]), &(to->equipped[i]));
  }
}

void player::copy_inventory_storage(TInventoryData *from, TInventoryData *to)
{
  for (int i = 0; i < STORAGE_SIZE; ++i)
  {
	spawners::copy_item(&(from->storage[i]), &(to->storage[i]));
  }
}

void player::copy_inventory_bank(TInventoryData *from, TInventoryData *to)
{
  for (int i = 0; i < BANK_SIZE; ++i)
  {
	spawners::copy_item(&(from->bank[i]), &(to->bank[i]));
  }
}

void player::copy_inventory_backpack(TInventoryData *from, TInventoryData *to)
{
  for (int i = 0; i < BACKPACK_SIZE; ++i)
  {
	spawners::copy_item(&(from->backpack[i]), &(to->backpack[i]));
  }
}

void player::copy_inventory_all(TInventoryData *from, TInventoryData *to)
{
  copy_inventory_backpack(from, to); //копирование сумки
  copy_inventory_bank(from, to); //копирование банка
  copy_inventory_equipped(from, to); //копирование надетого снаряжения
  copy_inventory_storage(from, to); //копирование хранилища
}

void player::swap_inventory_equipped(TInventoryData *from, TInventoryData *to)
{
  TInventoryData buf;
  copy_inventory_equipped(to, &buf);
  copy_inventory_equipped(from, to);
  copy_inventory_equipped(&buf, from);
}

void player::swap_inventory_backpack(struct TInventoryData *from, struct TInventoryData *to)
{
  TInventoryData buf;
  copy_inventory_backpack(to, &buf);
  copy_inventory_backpack(from, to);
  copy_inventory_backpack(&buf, from);
}

void player::swap_inventory_bank(struct TInventoryData *from, struct TInventoryData *to)
{
  TInventoryData buf;
  copy_inventory_bank(to, &buf);
  copy_inventory_bank(from, to);
  copy_inventory_bank(&buf, from);
}

void player::swap_inventory_storage(TInventoryData *from, TInventoryData *to)
{
  TInventoryData buf;
  copy_inventory_storage(to, &buf);
  copy_inventory_storage(from, to);
  copy_inventory_storage(&buf, from);
}

void player::swap_inventory_all(TInventoryData *from, TInventoryData *to)
{
  TInventoryData buf;
  copy_inventory_all(to, &buf);
  copy_inventory_all(from, to);
  copy_inventory_all(&buf, from);
}

void player::clear_inventory_equipped(TInventoryData *inv)
{
  for (int i = 0; i < ES_SIZE; ++i)
  {
    spawners::clear_item(&(inv->equipped[i]));
  }
}

void player::clear_inventory_storage(TInventoryData *inv)
{
  for (int i = 0; i < STORAGE_SIZE; ++i)
  {
    spawners::clear_item(&(inv->storage[i]));
  }
}

void player::clear_inventory_bank(TInventoryData *inv)
{
  for (int i = 0; i < BANK_SIZE; ++i)
  {
    spawners::clear_item(&(inv->bank[i]));
  }
}

void player::clear_inventory_backpack(TInventoryData *inv)
{
  for (int i = 0; i < BACKPACK_SIZE; ++i)
  {
    spawners::clear_item(&(inv->backpack[i]));
  }
}

void player::clear_inventory_all(TInventoryData *inv)
{
  clear_inventory_backpack(inv);
  clear_inventory_bank(inv);
  clear_inventory_equipped(inv);
  clear_inventory_storage(inv);
}

bool player::inventory_slot_is_free(spawners::TItemIgData *slot)
{
  bool res = true;
  spawners::TItemIgData checker;
  spawners::clear_item(&checker);
  res &= (slot->cost == checker.cost);
  res &= (slot->def == checker.def);
  res &= (slot->disposable == checker.disposable);
  res &= (slot->dist == checker.dist);
  res &= (slot->hpbons == checker.hpbons);
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    res &= (slot->dmg[i] == checker.dmg[i]);
    res &= (slot->durability[i] == checker.durability[i]);
  }
  res &= (slot->ifstack == checker.ifstack);
  res &= (slot->kind == checker.kind);
  res &= (slot->lvlreq == checker.lvlreq);
  for (int i = 0; i < STATS_COUNT; ++i)
  {
    res &= (slot->statreq[i] == checker.statreq[i]);
    res &= (slot->statbons[i] == checker.statbons[i]);
  }
  res &= (slot->usable == checker.usable);
  res &= (slot->ntbons == checker.ntbons);
  res &= (slot->name == checker.name);
  res &= (slot->manufacturer == checker.manufacturer);
  res &= (slot->stack == checker.stack);
  res &= (slot->description == checker.description);
  res &= (slot->rarity == checker.rarity);
  for (int i = 0; i < ES_SIZE; ++i)
  {
    res &= (slot->slots[i] == checker.slots[i]);
  }
  return res;
}

int player::inventory_first_free_backpack(TInventoryData *data)
{
  int res = FREE_INDEX;
  for (int i = 0; i < BACKPACK_SIZE; ++i)
  {
    if (inventory_slot_is_free(&(data->backpack[i])))
    {
      res = i;
      break;
    }
  }
  return res;
}

int player::inventory_first_free_bank(TInventoryData *data)
{
  int res = FREE_INDEX;
  for (int i = 0; i < BANK_SIZE; ++i)
  {
    if (inventory_slot_is_free(&(data->bank[i])))
    {
      res = i;
      break;
    }
  }
  return res;
}

int player::inventory_first_free_storage(TInventoryData *data)
{
  int res = FREE_INDEX;
  for (int i = 0; i < STORAGE_SIZE; ++i)
  {
    if (inventory_slot_is_free(&(data->storage[i])))
    {
      res = i;
      break;
    }
  }
  return res;
}

int player::inventory_count_free_slots_backpack(TInventoryData *data)
{
  int res = ZERO;
  for (int i = 0; i < BACKPACK_SIZE; ++i)
  {
    if (inventory_slot_is_free(data->backpack[i]))
    {
      res++;
    }
  }
  return res;
}

int player::inventory_count_free_slots_bank(TInventoryData *data)
{
  int res = ZERO;
  for (int i = 0; i < BANK_SIZE; ++i)
  {
    if (inventory_slot_is_free(&(data->bank[i])))
    {
      res++;
    }
  }
  return res;
}

int player::inventory_count_free_slots_storage(TInventoryData *data)
{
  int res = ZERO;
  for (int i = 0; i < STORAGE_SIZE; ++i)
  {
    if (inventory_slot_is_free(&(data->storage[i])))
    {
      res++;
    }
  }
  return res;
}

void player::copy_player_data(TPlayerData *from, TPlayerData *to)
{
  for (int i = 0; i < STATS_COUNT; ++i)
  {
    to->stats[i] = from->stats[i];
  }
  to->sp = from->sp;
  to->name = from->name;
  to->nutrition = from->nutrition; 
  to->level = from->level; 
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    to->exp[i] = from->exp[i];
    to->hp[i] = from->hp[i];
  }
}

void player::swap_player_data(struct TPlayerData *from, struct TPlayerData *to)
{
  TPlayerData buf;
  copy_player_data(to, &buf);
  copy_player_data(from, to);
  copy_player_data(&buf, from);
}

void player::clear_player_data(struct TPlayerData *data)
{
  for (int i = 0; i < STATS_COUNT; ++i)
  {
    data->stats[i] = FREE_INDEX;
  }
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    data->exp[i] = FREE_INDEX;
    data->hp[i] = FREE_INDEX;
  }
  data->level = FREE_INDEX;
  data->nutrition = FREE_INDEX;
  data->sp = FREE_INDEX;
  data->name.clear();
}



player::Player::Player()
{
  char_data.name.clear();
  char_data.level = START_LEVEL;
  char_data.exp[0] = ZERO;
  char_data.exp[1] = FIRST_LEVELUP_CAP;
  for (int i = 0; i < STATS_COUNT; ++i)
  {
    char_data.stats[i] = INITIAL_STATS_VALUE;
  }
  char_data.nutrition = MAX_NUTRITION_VALUE; //
  char_data.sp = LEVELUP_SP_GRANT * 2; //
  char_data.hp[1] = char_data.stats[3] * HP_PER_STAT_POINT; //
  char_data.hp[0] = char_data.hp[1]; //
  clear_inventory_all(&items); //
}

player::Player::Player(struct TPlayerData inp_char, struct TInventoryData inp_items)
{
  char_data.name = inp_char.name;
  char_data.level = inp_char.level;
  char_data.nutrition = inp_char.nutrition;
  char_data.sp = inp_char.sp;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    char_data.exp[i] = inp_char.exp[i];
    char_data.hp[i] = inp_char.hp[i];
  }
  for (int i = 0; i < STATS_COUNT; ++i)
  {
    char_data.stats[i] = inp_char.stats[i];
  }
  copy_inventory_all(&inp_items, &items);
}

player::Player::~Player()
{
}

void player::Player::stat_up(int stat_index)
{
  if (char_data.sp > 0)
  {
    char_data.sp--;
    char_data.stats[stat_index]++;
  }
}

void player::Player::level_up()
{
  char_data.level++;
  char_data.sp += LEVELUP_SP_GRANT;
  {
    double new_hp_cap;
    new_hp_cap = char_data.hp[1] * HP_CAP_RAISE;
    char_data.hp[1] = round(new_hp_cap);
    char_data.hp[0] = char_data.hp[1];
  }
  {
    double new_exp_cap;
    new_exp_cap = char_data.exp[1] + char_data.exp[1] * EXP_CAP_RAISE;
    char_data.exp[1] = round(new_exp_cap);
  }
}
bool player::Player::add_item(spawners::TItemIgData *item)
{
  bool res = false; //по умолчанию считаем, что не удалось добавить предмет
  if (inventory_count_free_slots_backpack(&items) > ZERO)
  {
    spawners::copy_item(item, &(items.backpack[inventory_first_free_backpack(&items)]));
    res = true;
  }
  return res;
}

void player::Player::remove_item(TInventorySections section, int slot)
{
  int size = ZERO;
  switch (section)
  {
    case IS_EQUIPPED:
	{
      size = ES_SIZE;
      if (slot < size)
      {
        spawners::clear_item(&(items.equipped[slot]));
      }
      break;
    }
    case IS_BACKPACK:
    {
      size = BACKPACK_SIZE;
      if (slot < size)
      {
        spawners::clear_item(&(items.backpack[slot]));
      }
      break;
    }
    case IS_BANK:
    {
      size = BANK_SIZE;
      if (slot < size)
      {
        spawners::clear_item(&(items.bank[slot]));
      }
      break;
    }
	case IS_STORAGE:
    {
      size = STORAGE_SIZE;
      if (slot < size)
      {
        spawners::clear_item(&(items.storage[slot]));
      }
      break;
    }
  }
}

bool player::Player::swap_items(TInventorySections from_section, int from_slot, TInventorySections to_section, int to_slot)
{
  bool res = false;
  switch (from_section)
  {
    case IS_EQUIPPED:
    {
      switch (to_section)
      {
        case IS_EQUIPPED:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < ES_SIZE) && (to_slot > FREE_INDEX) && (to_slot < ES_SIZE))
          {
            if (items.equipped[from_slot].slots[to_slot] && items.equipped[to_slot].slots[from_slot])
            {
              res = true;
              spawners::swap_item(&(items.equipped[from_slot]), &(items.equipped[to_slot]));
            }
          }
          break;
        }
        case IS_BACKPACK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < ES_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BACKPACK_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.backpack[to_slot].statreq[i]);
            }
            if (res1 && items.backpack[to_slot].slots[from_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[from_slot].statbons[i];
                char_data.stats[i] += items.backpack[to_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[from_slot]), &(items.backpack[to_slot]));
            }
          }
          break;
        }
        case IS_BANK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < ES_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BANK_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.bank[to_slot].statreq[i]);
            }
            if (res1 && items.bank[to_slot].slots[from_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[from_slot].statbons[i];
                char_data.stats[i] += items.bank[to_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[from_slot]), &(items.bank[to_slot]));
            }
          }
          break;
        }
        case IS_STORAGE:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < ES_SIZE) && (to_slot > FREE_INDEX) && (to_slot < STORAGE_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.storage[to_slot].statreq[i]);
            }
            if (res1 && items.storage[to_slot].slots[from_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[from_slot].statbons[i];
                char_data.stats[i] += items.storage[to_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[from_slot]), &(items.storage[to_slot]));
            }
          }
          break;
        }
      }
      break;
    }
    case IS_BACKPACK:
    {
      switch (to_section)
      {
        case IS_EQUIPPED:
        {
          if ((to_slot > FREE_INDEX) && (to_slot < ES_SIZE) && (from_slot > FREE_INDEX) && (from_slot < BACKPACK_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.backpack[from_slot].statreq[i]);
            }
            if (res1 && items.backpack[from_slot].slots[to_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[to_slot].statbons[i];
                char_data.stats[i] += items.backpack[from_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[to_slot]), &(items.backpack[from_slot]));
            }
          }
          break;
        }
        case IS_BACKPACK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BACKPACK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BACKPACK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.backpack[from_slot]), &(items.backpack[to_slot]));
          }
          break;
        }
        case IS_BANK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BACKPACK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BANK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.backpack[from_slot]), &(items.bank[to_slot]));
          }
          break;
        }
        case IS_STORAGE:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BACKPACK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < STORAGE_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.backpack[from_slot]), &(items.storage[to_slot]));
          }
          break;
        }
      }
      break;
    }
    case IS_BANK:
    {
      switch (to_section)
      {
        case IS_EQUIPPED:
        {
          if ((to_slot > FREE_INDEX) && (to_slot < ES_SIZE) && (from_slot > FREE_INDEX) && (from_slot < BANK_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.bank[from_slot].statreq[i]);
            }
            if (res1 && items.bank[from_slot].slots[to_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[to_slot].statbons[i];
                char_data.stats[i] += items.bank[from_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[to_slot]), &(items.bank[from_slot]));
            }
          }
          break;
        }
        case IS_BACKPACK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BANK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BACKPACK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.bank[from_slot]), &(items.backpack[to_slot]));
          }
          break;
        }
        case IS_BANK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BANK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BANK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.bank[from_slot]), &(items.bank[to_slot]));
          }
          break;
        }
        case IS_STORAGE:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < BANK_SIZE) && (to_slot > FREE_INDEX) && (to_slot < STORAGE_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.bank[from_slot]), &(items.storage[to_slot]));
          }
          break;
        }
      }
      break;
    }
    case IS_STORAGE:
    {
      switch (to_section)
      {
        case IS_EQUIPPED:
        {
          if ((to_slot > FREE_INDEX) && (to_slot < ES_SIZE) && (from_slot > FREE_INDEX) && (from_slot < STORAGE_SIZE))
          {
            bool res1 = true;
            for (int i = 0; i < STATS_COUNT; ++i)
            {
              res1 &= (char_data.stats[i] >= items.storage[from_slot].statreq[i]);
            }
            if (res1 && items.storage[from_slot].slots[to_slot])
            {
              res = true;
              for (int i = 0; i < STATS_COUNT; ++i)
              {
                char_data.stats[i] -= items.equipped[to_slot].statbons[i];
                char_data.stats[i] += items.storage[from_slot].statbons[i];
              }
              spawners::swap_item(&(items.equipped[to_slot]), &(items.storage[from_slot]));
            }
          }
          break;
        }
        case IS_BACKPACK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < STORAGE_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BACKPACK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.storage[from_slot]), &(items.backpack[to_slot]));
          }
          break;
        }
        case IS_BANK:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < STORAGE_SIZE) && (to_slot > FREE_INDEX) && (to_slot < BANK_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.backpack[from_slot]), &(items.bank[to_slot]));
          }
          break;
        }
        case IS_STORAGE:
        {
          if ((from_slot > FREE_INDEX) && (from_slot < STORAGE_SIZE) && (to_slot > FREE_INDEX) && (to_slot < STORAGE_SIZE))
          {
            res = true;
            spawners::swap_item(&(items.storage[from_slot]), &(items.storage[to_slot]));
          }
          break;
        }
      }
      break;
    }
  }
  return res;
}

int player::Player::get_stat(int ind)
{
  if ((ind >= ZERO) && (ind < STATS_COUNT))
  {
    return char_data.stats[ind];
  }
  else
  {
    return FREE_INDEX;
  }
}

int player::Player::get_level()
{
  return char_data.level;
}

int player::Player::get_sp()
{
  return char_data.sp;
}

int player::Player::get_exp(int ind)
{
  if ((ind >= ZERO) && (ind < PAIR_ARR_SIZE))
  {
    return char_data.exp[ind];
  }
  else
  {
    return FREE_INDEX;
  }
}

int player::Player::get_hp(int ind)
{
  if ((ind >= ZERO) && (ind < PAIR_ARR_SIZE))
  {
    return char_data.hp[ind];
  }
  else
  {
    return FREE_INDEX;
  }
}

int player::Player::get_nutrition()
{
  return char_data.nutrition;
}

std::string player::Player::get_name()
{
  return char_data.name;
}

spawners::TItemIgData player::Player::get_item(TInventorySections section, int ind)
{
  spawners::TItemIgData res;
  spawners::clear_item(&res);
  switch (section)
  {
    case IS_EQUIPPED:
    {
      if ((ind >= ZERO) && (ind < ES_SIZE))
      {
        spawners::copy_item(&(items.equipped[ind]), &res);
      }
      break;
    }
    case IS_BACKPACK:
    {
      if ((ind >= ZERO) && (ind < BACKPACK_SIZE))
      {
        spawners::copy_item(&(items.backpack[ind]), &res);
      }
      break;
    }
    case IS_BANK:
    {
      if ((ind >= ZERO) && (ind < BANK_SIZE))
      {
        spawners::copy_item(&(items.bank[ind]), &res);
      }
      break;
    }
    case IS_STORAGE:
    {
      if ((ind >= ZERO) && (ind < STORAGE_SIZE))
      {
        spawners::copy_item(&(items.storage[ind]), &res);
      }
      break;
    }
  }
  return res;
}

void player::Player::set_stat(int ind, int value, TFieldEditorKind kind)
{
  if ((ind >= ZERO) && (ind < STATS_COUNT))
  {
    switch (kind)
    {
      case FE_INCREASE:
      {
        char_data.stats[ind] += value;
        break;
      }
      case FE_DECREASE:
      {
        char_data.stats[ind] -= value;
        break;
      }
      case FE_REPLACE:
      {
        char_data.stats[ind] = value;
        break;
      }
    }
  }
}

void player::Player::set_level(int value, TFieldEditorKind kind)
{
  switch (kind)
  {
    case FE_INCREASE:
    {
      char_data.level += value;
      break;
    }
    case FE_DECREASE:
    {
      char_data.level -= value;
      break;
    }
    case FE_REPLACE:
    {
      char_data.level = value;
      break;
    }
  }
  if (char_data.level < START_LEVEL)
  {
    char_data.level = START_LEVEL;
  }
}

void player::Player::set_sp(int value, TFieldEditorKind kind)
{
  switch (kind)
  {
    case FE_INCREASE:
    {
      char_data.sp += value;
      break;
    }
    case FE_DECREASE:
    {
      char_data.sp -= value;
      break;
    }
    case FE_REPLACE:
    {
      char_data.sp = value;
      break;
    }
  }
  if (char_data.sp < ZERO)
  {
    char_data.level = ZERO;
  }
}

void player::Player::set_nutrition(int value, TFieldEditorKind kind)
{
  switch (kind)
  {
    case FE_INCREASE:
    {
      char_data.nutrition += value;
      break;
    }
    case FE_DECREASE:
    {
      char_data.nutrition -= value;
      break;
    }
    case FE_REPLACE:
    {
      char_data.nutrition = value;
      break;
    }
  }
  if (char_data.nutrition < MIN_NUTRITION_VALUE)
  {
    char_data.nutrition = MIN_NUTRITION_VALUE;
  }
  else
  {
    if (char_data.nutrition > MAX_NUTRITION_VALUE)
    {
      char_data.nutrition = MAX_NUTRITION_VALUE;
    }
  }
}

void player::Player::set_name(std::string value)
{
  char_data.name = value;
}

void player::Player::set_exp(int ind, int value, TFieldEditorKind kind)
{
  if ((ind >= ZERO) && (ind < PAIR_ARR_SIZE))
  {
    switch (kind)
    {
      case FE_INCREASE:
      {
        char_data.exp[ind] += value;
        break;
      }
      case FE_DECREASE:
      {
        char_data.exp[ind] -= value;
        break;
      }
      case FE_REPLACE:
      {
        char_data.exp[ind] = value;
        break;
      }
    }
    if (char_data.exp[ind] < ZERO)
    {
      char_data.exp[ind] = ZERO;
    }
  }
}

void player::Player::set_hp(int ind, int value, TFieldEditorKind kind)
{
  switch (kind)
  {
    case FE_INCREASE:
    {
      char_data.hp[ind] += value;
      break;
    }
    case FE_DECREASE:
    {
      char_data.hp[ind] -= value;
      break;
    }
    case FE_REPLACE:
    {
      char_data.hp[ind] = value;
      break;
    }
  }
  if (char_data.hp[ind] < ZERO)
  {
    char_data.hp[ind] = ZERO;
  }
  if (char_data.hp[0]>char_data.hp[1])
  {
    int buf = char_data.hp[1];
    char_data.hp[1] = char_data.hp[0];
    char_data.hp[0] = buf;
  }
}

player::TPlayerData player::Player::eject_pdata()
{
  return char_data;
}

player::TInventoryData player::Player::eject_idata()
{
  return items;
}