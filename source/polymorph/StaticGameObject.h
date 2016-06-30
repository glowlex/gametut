#pragma once

#ifndef STATICGAMEOBJECT_H
#define STATICGAMEOBJECT_H

#include "GameObject.h"

using namespace generic_consts;
using namespace prototypes;

class StaticGameObject: public GameObject {
  public:
    StaticGameObject();
	virtual ~StaticGameObject();
	unsigned char* get_description();
	int get_pic_name(std::string &out) { return 0; }
  protected:    
    unsigned char* _description;
};
  
#endif
