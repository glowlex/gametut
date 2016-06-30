#ifndef ACTION_H
#define ACTION_H

#include "prototypes.h"
#include "AliveGameObject.h"

class Action {
  public:
  	Action() {}
  	virtual ~Action() {}
    virtual int implement() = 0;
    virtual AliveGameObject* get_sender() = 0;
};

#endif
