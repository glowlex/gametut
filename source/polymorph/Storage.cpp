#include "Storage.h"

Storage::~Storage() {
  for (size_t i = 0; i < _size; ++i) {
    if (_content[i] != NULL) {
      delete _content[i];
	}
  }
  delete[] _content;
}

int Storage::count_free_slots(int &result) {
  result = 0;
  for (size_t i = 0; i < _size; ++i) {
    if (_content[i] == NULL) {
      ++result;
	}
  }
  return 0;
}

int Storage::first_free_slot(int &result) {
  result = -1;
  for (size_t i = 0; i < _size; ++i) {
    if (_content[i] == NULL) {
      result = i;
      break;
	}
  }
  return 0;
}

int Storage::add_item(Item* &new_item) {
  int index;
  int response = first_free_slot(index);
  _content[index] = new_item;
  new_item = NULL;
  return response;
}

int Storage::add_item(Item* &new_item, int index) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  _content[index] = new_item;
  new_item = NULL;
  return 0;
}

int Storage::get_item(int index, Item* &result) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  result = _content[index];
  return 0;
}

int Storage::get_index(Item* &address) {
  int result = FREE_INDEX;
  for (size_t i = 0; i < _size; ++i) {
    if (address == _content[i]) {
      result = i;
	}
  }
  return result;
}

int Storage::remove_item(int to_delete) {
  if (to_delete < 0 || to_delete >= _size) {
    return 0;
  }
  delete _content[to_delete];
  return 0;
}

int Storage::swap_items(int from_index, Inventory* &to_bag, int to_index) {
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

int Storage::swap_items(int from_index, int to_index) {
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

int Storage::use_item(int index, AliveGameObject* &user) {
  if (index < 0 || index >= _size) {
    return 0;
  }
  return _content[index]->use(user);
}

int Storage::get_size(int &result) {
  result = _size;
  return 0;
}
