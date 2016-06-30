#include "World.h"

World::World(char* name) {
  _playground = new Playground(name);
  _backend_query.clear();
  //_input_query.clear();
  //_output_query.clear();
}

World::~World() {
  delete _playground;
  for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_backend_query[i] != NULL) {
      delete _backend_query[i];
	}
  }
  /* for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_input_query[i] != NULL) {
      delete _input_query[i];
	}
  } */
  /* for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_output_query[i] != NULL) {
      delete _input_query[i];
	}
  } */
}

int World::render() {
  // code for frontend user input query
  /* for (size_t i = 0; i < _input_query.size(); ++i) {
    if (_input_query[i] != NULL) {
      _input_query[i]->execute();
      delete _input_query[i];
    }
  } */
  for (size_t i = 0; i < _backend_query.size(); ++i) {
    if (_backend_query[i] != NULL) {
      _backend_query[i]->execute();
      delete _backend_query[i];
	}
  }
  // code for frontend graphics output query 
  /* for (size_t i = 0; i < _output_query.size(); ++i) {
    if (_output_query[i] != NULL) {
      _output_query[i]->execute();
      delete _output_query[i];
	}
  } */
  return 0;
}
