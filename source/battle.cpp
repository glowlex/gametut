#pragma once

#include "battle.h"


void battle::copy_action_data(TAction *from, TAction *to)
{
  to->id = from->id;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    to->sender_ids[i] = from->sender_ids[i];
    to->target_ids[i] = from->target_ids[i];
  }
}

void battle::swap_action_data(TAction *from, TAction *to)
{
  TAction buf;
  copy_action_data(to, &buf);
  copy_action_data(from, to);
  copy_action_data(&buf, from);
}

void battle::clear_action_data(TAction *data)
{
  data->id;
  for (int i = 0; i < PAIR_ARR_SIZE; ++i)
  {
    data->sender_ids[i] = FREE_INDEX;
	data->target_ids[i] = FREE_INDEX;
  }
}




battle::Battlefield::Battlefield()
{
}

battle::Battlefield::~Battlefield()
{
}

int battle::Battlefield::spawn_prob(int spawned, int dp)
{
  int res = PERCENT_CAP - spawned*dp;
  if (res < ZERO)
  {
    res = ZERO;
  }
  return res;
}

bool battle::Battlefield::pack_has_leader(int pack_id)
{
  bool res = false;
  for (int i = 0; i < enemies[pack_id].size(); ++i)
  {
    if (enemies[pack_id][i].is_leader)
    {
      res = true;
      break;
    }
  }
  return res;
}

bool battle::Battlefield::have_mass_leader()
{
  bool res = false;
  for (int i = 0; i < enemies.size(); ++i)
  {
    for (int j = 0; j < enemies[i].size(); ++j)
    {
      if (enemies[i][j].is_mass_leader)
      {
        res = true;
        break;
      }
    }
    if (res)
    {
      break;
    }
  }
  return res;
}

void battle::Battlefield::spawn_new_mob(database::Database *db, int mob_id, int pack_id, int llc, int hlc)
{
  enemies[pack_id].resize(enemies[pack_id].size() + 1);
  database::TMobStData mob_tmp = db->get_mob(mob_id);
  spawners::TMobIgData spawned = spawners::Mob::spawn(&mob_tmp, llc, hlc);
  spawners::copy_mob_data(&spawned, &(enemies[pack_id][enemies[pack_id].size() - 1]));
  spawners::Mob::Check_Leadership(&(enemies[pack_id][enemies[pack_id].size() - 1]), pack_has_leader(pack_id), have_mass_leader());
}

void battle::Battlefield::spawn_new_pack(database::Database *db, int mob_id, int llc, int hlc)
{
  srand(static_cast<unsigned int>(time(0)));
  enemies.resize(enemies.size() + 1);
  enemies[enemies.size() - 1].clear();
  for (int i = 0; i < PACK_MAX_SIZE; ++i)
  {
    int rnd = rand() % PERCENT_MOD_CAP;
    if (rnd <= spawn_prob(enemies[enemies.size() - 1].size(), db->get_mob(mob_id).dp))
    {
      spawn_new_mob(db, mob_id, enemies.size() - 1, llc, hlc);
    }
    else
    {
      break;
    }
  }
}

void battle::Battlefield::clear_dead(database::Database *db, int llc, int hlc)
{
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < enemies.size(); ++i)
  {
    if (enemies[i].size() > ZERO)
    {
      for (int j = 0; j < enemies[i].size(); ++j)
      {
        if (enemies[i][j].hp[0] == ZERO)
        {
          database::TLootList list;
          clear_loot_list(&list);
          list = db->get_loot_list(enemies[i][j].loot);
          double tmp_cash = list.cash;
          double tmp_exp = list.exp;
          if (enemies[i][j].level > START_LEVEL)
          {
            for (int k = START_LEVEL; k < enemies[i][j].level; ++k)
            {
              tmp_cash *= (1.0 + spawners::CASH_RAISE);
              tmp_exp *= (1.0 + spawners::EXP_RAISE);
            }
          }
          if (enemies[i][j].is_leader)
          {
            tmp_cash *= spawners::LEADER_CASH_MODIFIER;
            tmp_exp *= spawners::LEADER_EXP_MODIFIER;
            for (int k = 0; k < enemies[i].size(); ++k)
            {
              if (k != j)
              {
                double tmp;
                for (int l = 0; l < PAIR_ARR_SIZE; ++l)
                {
                  tmp = enemies[i][k].dmg[l];
                  tmp /= (spawners::LEADER_DMG_MODIFIER * PACK_DEBUFF_MODIFIER);
                  enemies[i][k].dmg[l] = round(tmp);
                }
                tmp = enemies[i][k].def;
                tmp /= (spawners::LEADER_DEF_MODIFIER * PACK_DEBUFF_MODIFIER);
                enemies[i][k].def = round(tmp);
                tmp = enemies[i][k].hp[1];
                tmp /= (spawners::LEADER_HP_MODIFIER * PACK_DEBUFF_MODIFIER);
                enemies[i][k].hp[1] = round(tmp);
                if (enemies[i][k].hp[0] > enemies[i][k].hp[1])
                {
                  enemies[i][k].hp[0] = enemies[i][k].hp[1];
                }
                else
                {
                  tmp = enemies[i][k].hp[0];
                  tmp /= (spawners::LEADER_HP_MODIFIER * PACK_DEBUFF_MODIFIER);
                  enemies[i][k].hp[0] = round(tmp);
                }
              }
            }
            if (enemies[i][j].is_mass_leader)
            {
              double tmp;
              tmp_cash *= spawners::MASS_LEADER_CASH_MODIFIER;
              tmp_exp *= spawners::MASS_LEADER_EXP_MODIFIER;
              for (int k = 0; k < enemies.size(); ++k)
              {
                for (int l = 0; l < enemies[k].size(); ++l)
                {
                  tmp = enemies[k][l].def;
                  tmp /= (spawners::MASS_LEADER_DEF_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                  enemies[k][l].def = round(tmp);
                  tmp = enemies[k][l].hp[1];
                  tmp /= (spawners::MASS_LEADER_HP_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                  enemies[k][l].hp[1] = round(tmp);
                  if (enemies[k][l].hp[0]>enemies[k][l].hp[1])
                  {
                    enemies[k][l].hp[0] = enemies[k][l].hp[1];
                  }
                  else
                  {
                    tmp = enemies[k][l].hp[0];
                    tmp /= (spawners::MASS_LEADER_HP_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                    enemies[k][l].hp[0] = round(tmp);
                  }
                  for (int m = 0; m < PAIR_ARR_SIZE; ++m)
                  {
                    tmp = enemies[k][l].dmg[m];
                    tmp /= (spawners::MASS_LEADER_DMG_MODIFIER * (0.1 + PACK_DEBUFF_MODIFIER));
                    enemies[k][l].dmg[m] = round(tmp);
                  }
                }
              }
            }
          }
          reward_cash += round(tmp_cash);
          reward_exp += round(tmp_exp);
          for (int k = 0; k < LOOT_LIST_SIZE; ++k)
          {
            for (int l = 0; l < list.loot[k].max_quant; ++l)
            {
              int rnd = rand() % PERCENT_MOD_CAP;
              if (rnd <= list.loot[k].poss)
              {
                database::TItemStData data = db->get_item(list.loot[k].id);
                loot.resize(loot.size() + 1);
                spawners::TItemIgData item = spawners::Item::spawn(&data,llc,hlc);
                spawners::copy_item(&item, &(loot[loot.size() - 1]));
              }
            }
          }
          enemies[i].erase(enemies[i].begin() + j);
        }
      }
    }
  }
}

battle::TAction battle::AI::select(database::TNPCRole role, player::Player *pl, Battlefield *bf, int i, int j)
{
  switch (role)
  {
    case database::NR_NONDEF:
    {
      return AI::nondef_ai(pl, bf, i, j);
    }
    case database::NR_GRUNT:
    {
      return AI::grunt_ai(pl, bf, i, j);
    }
    case database::NR_DMG:
    {
      return AI::damager_ai(pl, bf, i, j);
    }
    case database::NR_SUPPORT:
    {
      return AI::healer_ai(pl, bf, i, j);
    }
  }
}

battle::TAction battle::AI::healer_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO };
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::damager_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO };
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::grunt_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO };
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}

battle::TAction battle::AI::nondef_ai(player::Player *pl, Battlefield *bf, int i, int j)
{
  TAction res;
  res.id = AL_IDLE;
  res.sender_ids[0] = i;
  res.sender_ids[1] = j;
  unsigned int variants[AL_SIZE] = { ZERO };
  for (int k = 0; k < bf->enemies.size(); ++k)
  {
    for (int l = 0; l < bf->enemies[k].size(); ++l)
    {
      if ((k != i) && (l != j))
      {
        
      }
    }
  }
  return res;
}
