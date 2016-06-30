#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <string>

class GameMap {
  public:
    GameMap() {}
    virtual ~GameMap() {}
    virtual int get_textures(int** &texture_map) = 0;
    virtual int what(int x_coord, int y_coord, std::string &out) = 0;
  protected:
    virtual int read_mask(int key, int** &byte_mask) = 0;
    virtual int merge_masks(int masks_count, int*** &masks, int* textures_id, int** &merged_mask) = 0;
};

#endif
