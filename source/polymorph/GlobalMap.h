#ifndef GLOBALMAP_H
#define GLOBALMAP_H

#include "prototypes.h"
#include "LocalMapObject.h"


class GlobalMap {
  public: 
    GlobalMap();
    GlobalMap(LocalMapObject*** &source);
    ~GlobalMap();
    
    LocalMapObject*** _map;
};

#endif
