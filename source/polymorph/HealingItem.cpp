#include "HealingItem.h"

HealingItem::HealingItem(TConsumablePrototype &prototype, int level): ConsumableItem() {
  _name = new unsigned char[NAMESTRING_SIZE];
  for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
    _name[i] = prototype._name[i];
    if (prototype._name[i] == '\0') {
      break;
    }
  }
  _description = new unsigned char[DESCRSTRING_SIZE];
  for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
    _description[i] = prototype._description[i];
    if (prototype._description[i] == '\0') {
      break;
    }
  }
  _stack = MIN_CONSUMABLE_STACK;
  _hp_restore = new int[PAIR_ARR_SIZE];
  _hp_restore[0] = prototype._effect;
  _hp_restore[1] = _hp_restore[0] * ITEM_DAMAGE_MINMAX_RATIO;
}
  
HealingItem::~HealingItem() {
  delete[] _hp_restore;
}
  
int* HealingItem::get_hp_restore() {
  return _hp_restore;
}
  
int HealingItem::use(AliveGameObject* user) {
  if (user != NULL) {
    srand(static_cast<unsigned int>(time(0)));
	int rnd = rand() % (_hp_restore[MAXIMAL_VALUE_INDEX] - _hp_restore[CURRENT_VALUE_INDEX]) + _hp_restore[CURRENT_VALUE_INDEX];
	--_stack;

    user->set_health(rnd);
    if (_stack <= 0) {
      _to_delete = true;
	}
  }
  return 0;    
}
  
int HealingItem::what(std::string &out) {
  out.clear();
  char* digit = new char[NAMESTRING_SIZE];
  out.append((char*)_name);
  out.append("\t consumable item\n--\n");
  out.append("level: ");
  out.append(itoa(_level, digit, 10));
  out.append("\n");
  out.append("quantity: ");
  out.append(itoa(_stack, digit, 10));
  out.append(" / ");
  out.append(itoa(MAX_CONSUMABLE_STACK, digit, 10));
  out.append("\n");
  out.append("cost: ");
  out.append(itoa(_cost, digit, 10));
  out.append("\n");
  out.append("heals: ");
  out.append(itoa(_hp_restore[CURRENT_VALUE_INDEX], digit, 10));
  out.append("-");
  out.append(itoa(_hp_restore[MAXIMAL_VALUE_INDEX], digit, 10));
  out.append(" hp\n");
  out.append((char*) _description);
  delete[] digit;
  return 0;
}

int HealingItem::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  char* digit = new char[NAMESTRING_SIZE / 2];
  prefix = "medicine_";
  exec = ".png";
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
