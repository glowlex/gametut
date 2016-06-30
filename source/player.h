#pragma once
#include "gtl_rpg.h"
#include "spawners.h"

namespace player
{
  using namespace gtl_rpg;
  using namespace spawners;

  const int BACKPACK_SIZE = 36;
  const int BANK_SIZE = 154;
  const int STORAGE_SIZE = 72;
  const int FIRST_LEVELUP_CAP = 100;
  const int INITIAL_STATS_VALUE = 10;
  const int LEVELUP_SP_GRANT = 5;
  const int HP_PER_STAT_POINT = 10;

  enum TInventorySections { IS_NONDEF = FREE_INDEX, IS_EQUIPPED, IS_BACKPACK, IS_BANK, IS_STORAGE, IS_SIZE };
  

  struct TInventoryData
  {
	  TItemIgData equipped[ES_SIZE];
	  TItemIgData backpack[BACKPACK_SIZE];
	  TItemIgData bank[BANK_SIZE];
	  TItemIgData storage[STORAGE_SIZE];
	  int cash;
  };

  struct TPlayerData
  {
    std::string name;
    int level;
    int nutrition;
    int exp[PAIR_ARR_SIZE];
    int hp[PAIR_ARR_SIZE];
    int sp;
    int stats[database::STATS_COUNT];
  };

  void copy_inventory_equipped(struct TInventoryData *from, struct TInventoryData *to);
  void copy_inventory_backpack(struct TInventoryData *from, struct TInventoryData *to);
  void copy_inventory_bank(struct TInventoryData *from, struct TInventoryData *to);
  void copy_inventory_storage(struct TInventoryData *from, TInventoryData *to);
  void copy_inventory_all(struct TInventoryData *from, struct TInventoryData *to);
  void swap_inventory_equipped(struct TInventoryData *from, struct TInventoryData *to);
  void swap_inventory_backpack(struct TInventoryData *from, struct TInventoryData *to);
  void swap_inventory_bank(struct TInventoryData *from, struct TInventoryData *to);
  void swap_inventory_storage(struct TInventoryData *from, struct TInventoryData *to);
  void swap_inventory_all(struct TInventoryData *from, struct TInventoryData *to);
  void clear_inventory_equipped(struct TInventoryData *inv);
  void clear_inventory_backpack(struct TInventoryData *inv);
  void clear_inventory_bank(struct TInventoryData *inv);
  void clear_inventory_storage(struct TInventoryData *inv);
  void clear_inventory_all(struct TInventoryData *inv);
  bool inventory_slot_is_free(struct TItemIgData *slot);
  int inventory_first_free_backpack(struct TInventoryData *data);
  int inventory_first_free_bank(struct TInventoryData *data);
  int inventory_first_free_storage(struct TInventoryData *data);
  int inventory_count_free_slots_backpack(struct TInventoryData *data);
  int inventory_count_free_slots_bank(struct TInventoryData *data);
  int inventory_count_free_slots_storage(struct TInventoryData *data);
  void copy_player_data(struct TPlayerData *from, struct TPlayerData *to);
  void swap_player_data(struct TPlayerData *from, struct TPlayerData *to);
  void clear_player_data(struct TPlayerData *data);

  class Player
  {
    public:

    Player();
    Player(struct TPlayerData inp_char, struct TInventoryData inp_items);
    ~Player();

    void stat_up(int stat_index);
    void level_up();

    bool add_item(struct spawners::TItemIgData *item);
    void remove_item(TInventorySections section, int slot);
    bool swap_items(TInventorySections from_section, int from_slot, TInventorySections to_section, int to_slot);


    int get_stat(int ind);
    int get_level();
    int get_sp();
    int get_exp(int ind);
    int get_hp(int ind);
    int get_nutrition();
    std::string get_name();
    spawners::TItemIgData get_item(TInventorySections section, int ind);
    void set_stat(int ind, int value, TFieldEditorKind kind);
    void set_level(int value, TFieldEditorKind kind);
    void set_sp(int value, TFieldEditorKind kind);
    void set_nutrition(int value, TFieldEditorKind kind);
    void set_name(std::string value);
    void set_exp(int ind, int value, TFieldEditorKind kind);
    void set_hp(int ind, int value, TFieldEditorKind kind);

    player::TPlayerData eject_pdata();
    player::TInventoryData eject_idata();

    private:
      TPlayerData char_data;
      TInventoryData items;
  };

}
