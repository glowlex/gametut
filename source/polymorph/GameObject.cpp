#include "GameObject.h"

  GameObject::GameObject() : _own_id(0), _pic_id(FREE_INDEX), _level(START_LEVEL), _name(NULL) {}

  GameObject::GameObject(int inp_level): _own_id(0), _pic_id(FREE_INDEX), _level(inp_level), _name(NULL) {}
  
  GameObject::~GameObject() {
    delete[] _name;
  }

  int GameObject::get_own_id() {
    return _own_id;
  }

  int GameObject::get_level() {
    return _level;
  }

  unsigned char* GameObject::get_name() {
    if (_name == NULL) { 
      unsigned char* res = _name;
      return res;
    } else {
      unsigned char* res = new unsigned char[NAMESTRING_SIZE];
      for (int i = 0; i < NAMESTRING_SIZE; ++i) {
        res[i] = _name[i];
      }
      return res;
    }
  }

