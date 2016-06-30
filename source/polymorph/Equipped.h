#ifndef EQUIPPED_H
#define EQUIPPED_H

#include "Inventory.h"
#include "EquipableItem.h"
#include "prototypes.h"

class Equipped: public Inventory {
  public:
  	
    Item** _content;
    
    Equipped(): _size(ES_SIZE) { _content = new Item*[ES_SIZE] {NULL}; }
	virtual ~Equipped();
    int first_free_slot(int &result) {
      result = -1;
      for (size_t i = 0; i < _size; ++i) {
        if (_content[i] == NULL) {
          result = i;
          break;
	    }
      }
      return 0;
    }
    
	int count_free_slots(int &result) {
      result = 0;
      for (size_t i = 0; i < _size; ++i) {
        if (_content[i] == NULL) {
          ++result;
	    }
      }
      return 0;
    }	
    int add_item(Item* &new_item);
    int add_item(Item* &new_item, int index);
    int get_item(int index, Item* &result);
    int get_index(Item* &address);
    int remove_item(int to_delete);
    int swap_items(int from_slot, Inventory* &to_bag, int to_slot);
    int swap_items(int from_index, int to_index);
    int use_item(int index, AliveGameObject* &user);
    int get_size(int &result);
    int get_stat_bonus(int* &result);
    int get_stat_bonus(int &result, int stat_index);
    int get_defense();
    void render();
    
  protected:
    int _size;
};

#endif
