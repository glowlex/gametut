#ifndef SQUAD_H
#define SQUAD_H

#include <vector>

#include "AliveGameObject.h"
#include "prototypes.h"

class Squad {
  public:
    Squad();
    Squad(int pack_id, int squad_size);
    virtual ~Squad();
    int get_pack_id() { return _pack_id; }
    int get_max_size() { return _max_size; }
    void set_pack_id(int value) { _pack_id = value; }
    int get_alive_count() { return _alive_count; }
    void set_alive_count(int value) { _alive_count += value; }
    int count_alive(int &result);
    int count_alive();
    
	int get_member_index(AliveGameObject* &to_find, int &result);
    int get_member_address(AliveGameObject* &result, int to_find);
    
    AliveGameObject** _members;
    
  protected:
    int _pack_id;
    int _alive_count;
    int _max_size;
};

#endif
