#include "QuestItem.h"

  QuestItem::QuestItem(TCollectablePrototype &prototype): CollectableItem() {
    _name = new unsigned char[NAMESTRING_SIZE];
    _description = new unsigned char[DESCRSTRING_SIZE];
    for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
      _name[i] = prototype._name[i];
	}
	for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
      _description[i] = prototype._description[i];
	}
	_quest_id = prototype._id;
	_cost = prototype._cost;
  }
  
  QuestItem::~QuestItem() {
  }
  
  int QuestItem::get_quest_id() {
    return _quest_id;
  }
  
  int QuestItem::get_pic_name(std::string &out) {
    out.clear();
    std::string prefix;
    std::string exec;
    char* digit = new char[NAMESTRING_SIZE / 2];
    prefix = "quest_item_";
    exec = " .png";
    out += prefix;
    out.append(itoa(_pic_id, digit, 10));
    out += exec;
    delete[] digit;
	return 0;
  }
