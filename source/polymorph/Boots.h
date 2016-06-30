
#pragma once

#ifndef BOOTS_H
#define BOOTS_H

#include "Armour.h"

class Boots: public Armour {
  public:
    Boots(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Armour(prototype, name, manufacturer, level){}
    ~Boots(){}
    int get_pic_name(std::string &out);
};

#endif
