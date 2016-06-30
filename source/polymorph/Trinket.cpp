#include "Trinket.h"

int Trinket::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  prefix = "implant_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE / 2];
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
