#include "Armour.h"

#pragma once

#ifndef HEAD_H
#define HEAD_H

class Head: public Armour {
  public:
    Head(TEquipablePrototype &prototype, unsigned char* name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Head() {}
    int get_pic_name(std::string &out);
};

#endif
