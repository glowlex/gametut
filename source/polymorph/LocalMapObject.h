#ifndef LOCAL_MAP_OBJECT_H
#define LOCAL_MAP_OBJECT_H

#include "StaticGameObject.h"
#include "AliveGameObject.h"
#include "prototypes.h"

#include <string>

#pragma once

class LocalMapObject: public StaticGameObject {
  public:
  	LocalMapObject();
  	LocalMapObject(TTilePrototype &prototype);
  	virtual ~LocalMapObject();

  	int get_texture_id() { return _texture_id; }
  	int get_defense() { return _defense; }
  	bool get_is_passable() { return _is_passable; }
  	int what(std::string &out);
	int get_pic_name(std::string &out) {return 0;}
  	AliveGameObject* _on_tile;
  	
  protected:
    int _texture_id;
    int _defense;
    bool _is_passable;
};

#endif
