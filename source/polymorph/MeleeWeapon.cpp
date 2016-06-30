#include "MeleeWeapon.h"
  
  MeleeWeapon::MeleeWeapon() : Weapon() {
  }

  MeleeWeapon::MeleeWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Weapon(prototype, name,  manufacturer, level) {
    _distance = 1;
  }
  
  MeleeWeapon::~MeleeWeapon() {
  }
  
