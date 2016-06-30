#include "prototypes.h"
#include <string>

#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

using namespace generic_consts;
using namespace prototypes;

class GameObject {
    public:
      GameObject();
      GameObject(int level);
      virtual ~GameObject();
      int get_own_id();
      int get_level();
      unsigned char* get_name();
      virtual int what(std::string &out) = 0;
      virtual int get_pic_name(std::string &out) = 0;

    protected:
      int _own_id;
      int _pic_id;
      int _level;
      unsigned char* _name;
};

#endif
