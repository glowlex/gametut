#include "Food.h"

Food::Food(TConsumablePrototype &prototype, int level): ConsumableItem() {
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
  _nutricity = prototype._effect;
}

int Food::what(std::string &out) {
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
  out.append("nutricity: ");
  out.append(itoa(_nutricity, digit, 10));
  out.append("\n");
  out.append((char*) _description);
  delete[] digit;
  return 0;
}

int Food::use(AliveGameObject* user) {
  if (user != NULL) {
    //food system in development. ATM food items could only be sold;
  }
  return 0;
}

int Food::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  char* digit = new char[NAMESTRING_SIZE / 2];
  prefix = "food_item_";
  exec = ".png";
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
