#include "UsableItem.h"

  UsableItem::UsableItem() : Item() {
    _level = START_LEVEL;
    _rarity = prototypes::IR_COMMON;
  }

  UsableItem::~UsableItem() {
  }

  TItemRareness UsableItem::get_rarity() {
    return _rarity;
  }

