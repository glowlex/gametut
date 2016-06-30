#pragma once

#ifndef ITEM_H
#define ITEM_H

#include "StaticGameObject.h"
#include "AliveGameObject.h"

using namespace generic_consts;
using namespace prototypes;

  class Item: public StaticGameObject {
    public:
      Item();
      virtual ~Item();
      int get_cost();
      bool get_in_bag();
      bool get_to_delete() { return _to_delete; }
      void set_to_delete(bool value);
      virtual int use(AliveGameObject* user) { return 0; }
    protected:
      int _cost;
      bool _in_bag;
      bool _to_delete;
  };

#endif
