#pragma once

#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

  class MeleeWeapon: public Weapon {
    public:
      MeleeWeapon();
      MeleeWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level);
      virtual ~MeleeWeapon();
  };
  
#endif
