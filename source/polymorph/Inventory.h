#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "AliveGameObject.h"

  class Inventory {
    public:
      Inventory() {}
      virtual ~Inventory() {}
      virtual int first_free_slot(int &result) = 0;
      virtual int count_free_slots(int &result) = 0;
      virtual int add_item(Item* &new_item) = 0;
      virtual int add_item(Item* &new_item, int index) = 0;
      virtual int get_item(int index, Item* &result) = 0;
      virtual int get_index(Item* &address) = 0;
      virtual int remove_item(int to_delete) = 0;
      virtual int swap_items(int from_slot, Inventory* &to_bag, int to_slot) = 0;
      virtual int swap_items(int from_index, int to_index) = 0;
      virtual int use_item(int index, AliveGameObject* &user) = 0;
      virtual int get_size(int &result) = 0;
      virtual int get_defense() = 0;
      virtual void render() = 0;
  };
  
#endif
