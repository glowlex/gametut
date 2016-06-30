#include "LocalMapObject.h"

LocalMapObject::LocalMapObject(): StaticGameObject() {
  _texture_id = FREE_INDEX;
  _defense = 0;
  _is_passable = false;
}

LocalMapObject::LocalMapObject(TTilePrototype &prototype): StaticGameObject() {
  _texture_id = prototype._texture;
  _defense = prototype._defense;
  _is_passable = prototype._is_passable;
  delete[] _description;
  delete[] _name;
  _description = new unsigned char[DESCRSTRING_SIZE] {};
  _name = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < DESCRSTRING_SIZE && prototype._description[i] != '\0'; ++i) {
    _description[i] = prototype._description[i];
  }
  for (size_t i = 0; i < NAMESTRING_SIZE && prototype._name; ++i)
  delete[] prototype._description;
  delete[] prototype._name;
  _on_tile = NULL;
}

LocalMapObject::~LocalMapObject() { _on_tile = NULL; }

int LocalMapObject::what(std::string &out) {
  out.clear();
  std::string str;
  char* digit = new char[NAMESTRING_SIZE / 2];
  str.clear();
  str.append((char*)_name);
  str.append("\n--\n");
  if (_defense > 0) {
  	str.append("defense: ");
    //str.append(itoa(_defense, digit, 10));
    str.append("\n");
  }
  if (_is_passable) {
    str.append("passable\n");
  } else {
    str.append("unpassable\n");
  }
  str.append("\n--\n");
  str.append((char*)_description);
  str.append("\n");
  out += str;
  delete[] digit;
  return OK_CODE;
}
/*
int LocalMapObject::get_pic_name(std::string &out) {
  out.clear();
  std::string prefix;
  std::string exec;
  prefix = "texture_";
  exec = ".png";
  char* digit = new char[NAMESTRING_SIZE];
  out += prefix;
  out.append(itoa(_texture_id, digit, 10));
  out += exec;
  delete[] digit;
  return 0;
}*/
