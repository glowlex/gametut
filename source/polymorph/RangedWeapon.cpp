#include "RangedWeapon.h"

  RangedWeapon::RangedWeapon() : Weapon() {
  }

  RangedWeapon::RangedWeapon(TEquipablePrototype &prototype, unsigned char*name, unsigned char* manufacturer, int level): Weapon(prototype, name, manufacturer, level) {
    _distance = prototype._distance;
  }

  RangedWeapon::~RangedWeapon() {
  }
