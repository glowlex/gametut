#include "NextLocationCommand.h"

int NextLocationCommand::execute() {
  if (_playground != NULL) {
    if (_playground->_battlefield != NULL) {
      bool is_end;
      bool is_victory;
      _playground->_battlefield->if_end_fight(is_victory, is_end);
      if (!is_end) {
      	return 0;
	  } else {
        if (is_victory) {
          delete _playground->_battlefield;
		} else {
          //game over comand here;
		}
	  }
	}
	delete _playground->_current_location;
	Forge* forge = new Forge("classic2.db");
	int response = forge->MakeLocation(rand() % LOCATION_PRESETS_COUNT + 1,_playground->_player->get_average_level(), &(_playground->_current_location));
	if(_playground->_current_location->entrance() == BATTLE_CODE) {
      _playground->_battlefield = new Battlefield(_playground->_current_location, _playground->_player);
	}
	delete forge;
  }
  return 0;
}
