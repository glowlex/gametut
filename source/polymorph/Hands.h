#pragma once

#ifndef HANDS_H
#define HANDS_H

#include "Armour.h"

class Hands : public Armour {
  public:
    Hands(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Armour(prototype, name, manufacturer, level) {}
    ~Hands() {}
    int get_pic_name(std::string &out);
};

#endif
