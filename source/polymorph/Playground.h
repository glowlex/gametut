#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Player.h"
#include "Battlefield.h"
#include "Settlement.h"
#include "Wildlands.h"

class Playground {
  public:
  	Playground(char* name) {
  	  _player = new Player(name);
	  _battlefield = NULL;
	  _current_location = NULL;	
	}
  	~Playground() {
  	  delete _player;
	  delete _battlefield;
	  delete _current_location;	
	}
  	
  	Player* _player;
    Battlefield* _battlefield;
    Location* _current_location;
};

#endif
