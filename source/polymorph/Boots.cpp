#include "Boots.h"

int Boots::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  switch (_kind) {
    case EK_LIGHT: {
      prefix = "light_";
      break;
	}
	case EK_MEDIUM: {
      prefix = "medium_";
	  break;
	}
	case EK_HEAVY: {
      prefix = "heavy_";
      break;
	}
  }
  prefix += "boots_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE / 2];
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}
