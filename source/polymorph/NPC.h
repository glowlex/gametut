#pragma once

#ifndef NPC_H
#define NPC_H

#include "StaticGameObject.h"

class NPC: public StaticGameObject {
  public:
    NPC(): StaticGameObject() { _speech = NULL; }
    virtual ~NPC() { delete[] _speech; }
  	
    virtual int speak(unsigned char* &out) = 0;
  	
  protected:
    unsigned char* _speech;
};

#endif
