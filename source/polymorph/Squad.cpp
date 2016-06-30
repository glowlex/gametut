#include "Squad.h"

Squad::Squad() {
  _members = NULL;
  _pack_id = FREE_INDEX;
  _alive_count = 0;
}

Squad::Squad(int pack_id, int squad_size) {
	_members = new AliveGameObject*[squad_size] {NULL};
	_pack_id = pack_id;
	_max_size = squad_size;
	_alive_count = 0;
}

Squad::~Squad() {
  for (size_t i = 0; i < _max_size; ++i) {
  	delete _members[i];
  }
  delete[] _members;
}
int Squad::count_alive(int &result) {
  result = 0;
  count_alive();
  result = _alive_count;
  return 0;
}

int Squad::count_alive() {
  _alive_count = 0;
  for(size_t i = 0; i < _max_size; ++i) {
    if (_members[i] != NULL) {
      ++_alive_count;
	}
  }
  return 0;
}

int Squad::get_member_address(AliveGameObject* &result, int to_find) {
  delete result;
  result = NULL;
  if (to_find > FREE_INDEX && to_find < _max_size) {
    result = _members[to_find];
  }
  return 0;
}

int Squad::get_member_index(AliveGameObject* &to_find, int &result) {
  result = FREE_INDEX;
  if (to_find != NULL) {
    for (size_t i = 0; i < _max_size; ++i) {
      if (_members[i] == to_find) {
        result = i;
        break;
	  }
	}
  }
  return 0;
}
