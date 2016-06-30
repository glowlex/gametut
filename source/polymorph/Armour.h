#pragma once

#ifndef ARMOUR_H
#define ARMOUR_H

#include "EquipableItem.h"

#include <cmath> 
#include <string>
#include <ctime>
#include <cstdlib>

  class Armour: public EquipableItem {
    public:
      Armour();
      Armour(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~Armour();
      int get_defense();
      TEquipmentKind get_kind();
      
      int what(std::string &out);
    protected:
      int _defense;
      TEquipmentKind _kind;
  };
  
#endif
