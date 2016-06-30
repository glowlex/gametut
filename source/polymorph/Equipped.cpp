#include "Equipped.h"

Equipped::~Equipped() {
  for (size_t i = 0; i < _size; ++i) {
    if (_content[i] != NULL) {
      delete _content[i];
	}
  }
  delete[] _content;
}

int Equipped::add_item(Item* &new_item) {
  int index;
  int response = first_free_slot(index);
  _content[index] = new_item;
  new_item = NULL;
  return response;
}

int Equipped::add_item(Item* &new_item, int index) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  _content[index] = new_item;
  new_item = NULL;
  return 0;
}

int Equipped::get_item(int index, Item* &result) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  result = _content[index];
  return 0;
}

int Equipped::get_index(Item* &address) {
  int result = FREE_INDEX;
  for (size_t i = 0; i < _size; ++i) {
    if (address == _content[i]) {
      result = i;
	}
  }
  return result;
}

int Equipped::remove_item(int to_delete) {
  if (to_delete < 0 || to_delete >= _size) {
    return 0;
  }
  _content[to_delete]->set_to_delete(true);
  return 0;
}

int Equipped::swap_items(int from_index, Inventory* &to_bag, int to_index) {
  if (from_index < 0 || from_index >= _size) {
    return 0;
  }
  int to_size = 0;
  to_bag->get_size(to_size);
  if (to_index < 0 || to_index >= to_size) {
    return 0;
  }
  Item* buffer = NULL;
  to_bag->get_item(to_index, buffer);
  to_bag->add_item(_content[from_index], to_index);
  _content[from_index] = buffer;
  buffer = NULL;
  return 0;
}

int Equipped::swap_items(int from_index, int to_index) {
  if (from_index < 0 || from_index >= _size) {
    return 0;
  }
  if (to_index < 0 || to_index >= _size) {
    return 0;
  }
  Item* buffer = _content[from_index];
  _content[from_index] = _content[to_index];
  _content[to_index] = _content[from_index];
  buffer = NULL;
  return 0;
}

int Equipped::use_item(int index, AliveGameObject* &user) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  return _content[index]->use(user);
}

int Equipped::get_size(int &result) {
  result = _size;
  return 0;
}

int Equipped::get_stat_bonus(int* &result) {
  delete[] result;
  result = new int[CS_SIZE] {0};
  for (size_t i = 0; i < ES_SIZE; ++i) {
    if (_content[i] != NULL) {
      int* tmp_bonus = NULL;
      EquipableItem* it = dynamic_cast<EquipableItem*>(_content[i]);
      tmp_bonus = it->get_stat_bons();
      for(size_t j = 0; j < CS_SIZE; ++j) {
      	result[j] += tmp_bonus[i];
	  }
	  delete[] tmp_bonus;
	}
  }
  return 0;
}

int Equipped::get_stat_bonus(int &result, int stat_index) {
  result = 0;
  if (stat_index > FREE_INDEX && stat_index < CS_SIZE) {
    for (size_t i = 0; i < ES_SIZE; ++i) {
      if (_content[i] != NULL) {
        int* tmp_bonus = NULL;
        EquipableItem* it = dynamic_cast<EquipableItem*>(_content[i]);
        tmp_bonus = it->get_stat_bons();
        result += tmp_bonus[stat_index];
        delete[] tmp_bonus;
	  }
	}
  }
  return 0;
}

int Equipped::get_defense() {
  int result = 0;
  for (size_t i = ES_HEAD; i < ES_WEAPON1; ++i) {
  	EquipableItem* it = dynamic_cast<EquipableItem*>(_content[i]);
    result += it->get_defense();
  }
  return result;
}

void Equipped::render() {
  for (size_t i = 0; i < _size; ++i) {
    if (_content[i]->get_to_delete()) {
      delete _content[i];
	}
  }
}
