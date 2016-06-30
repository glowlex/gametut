#include "LocalMap.h"

LocalMap::LocalMap(int* texture_ids, int* masks) {
  /*int*** masks_set = new int**[MAX_LOCAL_TEXTURES_COUNT];
  for (size_t i = 0; i < MAX_LOCAL_TEXTURES_COUNT; ++i) {
  	masks_set[i] = new int*[LOCAL_MAP_HEIGHT];
    for (size_t j = 0; j < LOCAL_MAP_HEIGHT; ++j) {
      masks_set[i][j] = new int[LOCAL_MAP_WIDTH];
	}
	read_mask(masks[i], masks_set[i]);
  }
  int** merged_mask = new int*[LOCAL_MAP_HEIGHT] {NULL};
  int** tmp_merged = new int*[LOCAL_MAP_HEIGHT] {NULL};
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    merged_mask[i] = new int[LOCAL_MAP_WIDTH] {0};
    tmp_merged[i] = new int[LOCAL_MAP_WIDTH] {0};
  }
  merge_masks(MAX_LOCAL_TEXTURES_COUNT, masks_set, texture_ids, tmp_merged);
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    for (size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      merged_mask[i][j] = tmp_merged[i][j];
	}
	delete[] tmp_merged[i];
  }
  delete[] tmp_merged;
  Forge* forge = new Forge("classic2.db");
  _map = new LocalMapObject**[LOCAL_MAP_HEIGHT];
  for(size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
  	_map[i] = new LocalMapObject*[LOCAL_MAP_WIDTH];
    for(size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      LocalMapObject* preset = NULL;
	  int response = forge->MakeTile(merged_mask[i][j], &preset);
      _map[i][j] = preset;
      preset = NULL;
	}
  }
  for(size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    delete[] merged_mask[i];
  }
  delete[] merged_mask;
  delete forge; */
}

LocalMap::~LocalMap() {
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    for (size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      delete _map[i][j];
	}
	delete[] _map[i];
  }
  delete[] _map;
}

int LocalMap::read_mask(int mask_key, int ** &byte_mask) {
 /* if (mask_key > 0 && mask_key <= LOCAL_MASKS_COUNT) {
  	int response;
  	int ** tmp_mask = new int*[LOCAL_MAP_HEIGHT] {NULL};
    for(size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
      delete[] byte_mask[i];
      byte_mask[i] = new int[LOCAL_MAP_WIDTH] {0};
      tmp_mask[i] = new int[LOCAL_MAP_WIDTH] {0};
	}
	Forge* forge = new Forge("classic2.db");
	response = forge->MakeMask(mask_key, true, tmp_mask);
	for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
      for (size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
        byte_mask[i][j] = tmp_mask[i][j];
	  }
	  delete[] tmp_mask[i];
	}
	delete[] tmp_mask;
    delete forge;
    return response;
  }*/
  return 0;
}

int LocalMap::merge_masks(int masks_count, int*** &masks, int* textures_id, int** &merged_mask) {
  int** tmp_merged = new int*[LOCAL_MAP_HEIGHT] {NULL};
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    tmp_merged[i] = new int[LOCAL_MAP_WIDTH] {0};
  }
  for (size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
    for (size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      for (size_t mask_no = 0; mask_no < masks_count; ++mask_no) {
        if (tmp_merged[i][j] < (masks[mask_no][i][j] * mask_no)) {
          tmp_merged[i][j] = mask_no;
		}
	  }
	  merged_mask[i][j] = textures_id[tmp_merged[i][j]];
	}
	delete[] tmp_merged[i];
  }
  delete[] tmp_merged;
  return 0;
}

int LocalMap::get_textures(int** &texture_map) {
  for(size_t i = 0; i < LOCAL_MAP_WIDTH; ++i) {
    delete[] texture_map[i];
  }
  delete[] texture_map;
  texture_map = new int*[LOCAL_MAP_HEIGHT];
  for(size_t i = 0; i < LOCAL_MAP_HEIGHT; ++i) {
  	texture_map[i] = new int[LOCAL_MAP_WIDTH];
    for(size_t j = 0; j < LOCAL_MAP_WIDTH; ++j) {
      texture_map[i][j] = _map[i][j]->get_texture_id();
	}
  }
  return 0;
}

int LocalMap::what(int x_coord, int y_coord, std::string &out) {
  if (_map[x_coord][y_coord]->_on_tile != NULL) {
    return _map[x_coord][y_coord]->_on_tile->what(out);
  } else {
    return _map[x_coord][y_coord]->what(out);
  }
}

