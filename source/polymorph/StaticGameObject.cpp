#include "StaticGameObject.h"

  StaticGameObject::StaticGameObject() : GameObject()  {
    _description = NULL;
  }

  StaticGameObject::~StaticGameObject() {
  	delete[] _description;
  }

  unsigned char* StaticGameObject::get_description() {
    if (_description == NULL) {
      return _description;
	} else {
      unsigned char* res = new unsigned char[DESCRSTRING_SIZE];
      for (int i = 0; i < DESCRSTRING_SIZE; ++i) {
        res[i] = _description[i];
	  }
	  return res;
	}
  }
