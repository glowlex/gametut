#pragma once

#ifndef TRADER_H
#define TRADER_H

#include "NPC.h"
#include "Item.h"
#include "prototypes.h"

class Trader: public NPC {
  public:
    Trader(): NPC() {_assortment = NULL;}
    virtual ~Trader() {}

    int get_charge() { return _charge; }
    int what(std::string &out) { return 0; }
    int speak(unsigned char* &out) { return 0; }
    
    Item** _assortment;

  protected:
    int _charge;
    virtual int form_assortment(TNPCPrototype &prototype, int level) = 0;
};

#endif
