
#pragma once

#ifndef CHEST_H
#define CHEST_H

#include "Armour.h"

class Chest : public Armour {
  public:
    Chest(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level) : Armour(prototype, name, manufacturer, level) {}
    ~Chest() {}
    int get_pic_name(std::string &out);
};

#endif
