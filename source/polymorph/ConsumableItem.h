#pragma once

#ifndef CONSUMABLEITEM_H
#define CONSUMABLEITEM_H

#include "UsableItem.h"
#include <cmath>

  class ConsumableItem: public UsableItem {
    public:
      ConsumableItem();
      virtual ~ConsumableItem();
      int get_stack();
      int change_stack(int &value, bool increase);
      int get_pic_name(std::string &out);
    protected:
      int _stack;
  };
  
#endif
