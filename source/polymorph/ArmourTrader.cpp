#include "ArmourTrader.h"

ArmourTrader::ArmourTrader(TNPCPrototype &prototype, int level): Trader() {
  _charge = prototype._charge * BASIC_VENDOR_CHARGE;
  form_assortment(prototype, level);
  delete[] _name;
  delete[] _description;
  delete[] _speech;
  _name = new unsigned char[NAMESTRING_SIZE] {};
  for (size_t i = 0; i < NAMESTRING_SIZE; ++i) {
  	_name[i] = prototype._name[i];
  }
  _description = new unsigned char [DESCRSTRING_SIZE] {};
  for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
    _description[i] = prototype._description[i];
  }
  _speech = new unsigned char [DESCRSTRING_SIZE] {};
  for (size_t i = 0; i < DESCRSTRING_SIZE; ++i) {
    _speech[i] = prototype._speech[i];
  }
}

ArmourTrader::~ArmourTrader() {
  for (size_t i =0; i < VENDOR_CAPACITY; ++i) {
    if (_assortment[i] != NULL) {
      delete _assortment[i];
	}
  delete[] _assortment;
  }
}

int ArmourTrader::form_assortment(TNPCPrototype &prototype, int level) {
  srand(static_cast<unsigned int>(time(0)));
  Forge* forge = new Forge("classic2.db");
  _assortment = new Item*[VENDOR_CAPACITY] {NULL};
  int items = rand() % VENDOR_CAPACITY + 1;
  for (size_t i = 0; i < items; ++i) {
    int key = rand() % (EK_TRINKET - EK_LIGHT) + 1 + prototype._content_id;
    Item* spawned = NULL;
    forge->MakeItem(key, level, &spawned);
    _assortment[i] = spawned;
    spawned = NULL;
  }
}
