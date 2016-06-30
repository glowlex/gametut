#pragma once

#ifndef USABLE_ITEM_H
#define USABLE_ITEM_H

#include "Item.h"

  class UsableItem: public Item {
    public:
      UsableItem();
      virtual ~UsableItem();
      TItemRareness get_rarity();
    protected:
      TItemRareness _rarity;
  };
  
#endif
