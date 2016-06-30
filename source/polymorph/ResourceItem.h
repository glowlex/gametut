#include "CollectableItem.h"

#pragma once

  class ResourceItem: public CollectableItem {
    public:
      ResourceItem(TCollectablePrototype &prototype): CollectableItem() { _resource_id = FREE_INDEX; }
      virtual ~ResourceItem() {}
      int get_resource_id() { return _resource_id; }
      int get_pic_name(std::string &out) { return 0; }
    protected:
      int _resource_id;
  };

