#include "Item.h"

  Item::Item() : StaticGameObject() {
    _cost = 0;
    _name = new unsigned char[NAMESTRING_SIZE];
    _description = new unsigned char[DESCRSTRING_SIZE];
  }

  Item::~Item() {
  }

  int Item::get_cost() {
    return _cost;
  } 
  
  bool Item::get_in_bag() {
    return _in_bag;
  }
  
