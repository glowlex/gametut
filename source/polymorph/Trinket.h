
#pragma once

#ifndef TRINKET_H
#define TRINKET_H

#include "Armour.h"

class Trinket: public Armour {
  public:
    Trinket(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Trinket(){}
    int get_pic_name(std::string &out);
};

#endif
