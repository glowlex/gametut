#include "GlobalMap.h"

GlobalMap::GlobalMap() {
  _map = new LocalMapObject**[GLOBAL_MAP_HEIGHT];
  for(size_t i = 0; i < GLOBAL_MAP_HEIGHT; ++i) {
    _map[i] = new LocalMapObject*[GLOBAL_MAP_WIDTH]{NULL};
  }
}

GlobalMap::GlobalMap(LocalMapObject*** &source) {
  _map = new LocalMapObject**[GLOBAL_MAP_HEIGHT];
  for(size_t i = 0; i < GLOBAL_MAP_HEIGHT; ++i) {
    _map[i] = new LocalMapObject*[GLOBAL_MAP_WIDTH];
    for (size_t j = 0; j < GLOBAL_MAP_WIDTH; ++i) {
      _map[i][j] = source[i][j];
      source[i][j] = NULL;
	}
	delete[] source[i];
  }
  delete[] source;
}

GlobalMap::~GlobalMap() {
  for (size_t i = 0; i < GLOBAL_MAP_HEIGHT; ++i) {
    for (size_t j = 0; j < GLOBAL_MAP_WIDTH; ++j) {
      delete _map[i][j];
	}
	delete[] _map[i];
  }
  delete[] _map;
}
