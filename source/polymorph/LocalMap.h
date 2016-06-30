#ifndef LOCALMAP_H
#define LOCALMAP_H

#include "GameMap.h"
#include "LocalMapObject.h"
#include "prototypes.h"

class LocalMap: public GameMap {
  public:
    LocalMap(int* texture_ids, int* masks);
    virtual ~LocalMap();
    int get_textures(int** &texture_map);
    int what(int x_coord, int y_coord, std::string &out);
  
    LocalMapObject*** _map;

  protected:
    int read_mask(int mask_key, int** &byte_mask);
    int merge_masks(int masks_count, int*** &masks, int* textures_id, int** &merged_mask);
};

#endif
