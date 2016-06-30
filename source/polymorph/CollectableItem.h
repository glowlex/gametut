#ifndef COLLECTABLE_ITEM_H
#define COLLECTABLE_ITEM_H

#include "Item.h"
#include <cmath>

#pragma once

  class CollectableItem: public Item {
    public:
      CollectableItem(): Item() { _stack = MIN_COLLECTABLE_STACK; }
      virtual ~CollectableItem() {}
      int get_stack() { return _stack; }
      int change_stack(int &value, bool increase) {
  	    int return_code = OK_CODE;
        if (increase) {
          _stack += value;
          if (_stack > MAX_COLLECTABLE_STACK) {
            value = _stack - MAX_COLLECTABLE_STACK;
            _stack = MAX_COLLECTABLE_STACK;
            return_code = OK_CODE;
	      }  
	    } else {
          _stack -= value;
          if (_stack < MIN_COLLECTABLE_STACK) {
            value = abs(_stack) - MIN_COLLECTABLE_STACK;
            if (value > EMPTY_STACK) {
              return_code = OK_CODE;
            }
            _stack = EMPTY_STACK;
          }
        }
        return return_code;
      }
    protected:
      int _stack;
  };
  
#endif
