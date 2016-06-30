#include "Head.h"

int Head::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  char* digit = new char[NAMESTRING_SIZE / 2];
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
  prefix += "helmet_";
  exec = ".png";
  out += prefix;
  out.append(itoa(_pic_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}