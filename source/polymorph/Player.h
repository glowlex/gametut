#ifndef PLAYER_H
#define PLAYER_H

#include "PartyMember.h"
#include "Squad.h"
#include "Equipped.h"
#include "Storage.h"
#include "Forge.h"
#include "NPC.h"
#include "WeaponTrader.h"
#include "ArmourTrader.h"
#include "MunitionsTrader.h"
#include "BlackMarket.h"
#include "prototypes.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
#include <string>

class Player {
  public:
    Player();
    Player(char* name);
    virtual ~Player();
    
    int hire(AliveGameObject* new_party_member);
    int fire(int to_fire_id, AliveGameObject* &to_save);
    int payday();
    int buy(NPC* trader, int to_buy_id);
    int sell(NPC* trader, int to_sell_id);
    int get_cash(int &result);
    int get_total_earned(int &result);
    int change_cash(int value);
    int get_average_level();
    int what(std::string &out);
    
    Squad* _squad;
    Inventory* _bag;
    Inventory* _storage;
    Inventory* _bank;
  protected:
    int _cash;
    int _total_earned;
    char* _company_name;
};

#endif
