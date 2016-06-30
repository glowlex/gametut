#include "CollectableItem.h"

#pragma once

  class QuestItem: public CollectableItem {
    public:
      QuestItem(TCollectablePrototype &prototype);
      virtual ~QuestItem();
      int get_quest_id();
      int get_pic_name(std::string &out);
    protected:
      int _quest_id; //change to Quest* after Quest class development
  };

