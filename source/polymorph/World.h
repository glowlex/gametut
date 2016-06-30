#ifndef WORLD_H
#define WORLD_H

#include "prototypes.h"
#include "RangedWeapon.h"
#include "MeleeWeapon.h"
#include "Head.h"
#include "Chest.h"
#include "Hands.h"
#include "Boots.h"
#include "Legs.h"
#include "Trinket.h"
#include "LocalMapObject.h"
#include "QuestGiver.h"
#include "ArmourTrader.h"
#include "WeaponTrader.h"
#include "MunitionsTrader.h"
#include "BlackMarket.h"
#include "GruntMonster.h"
#include "DamagerMonster.h"
#include "SupportMonster.h"
#include "CommonMonster.h"
#include "QuestMonster.h"
#include "PartyMember.h"
#include "Settlement.h"
#include "Wildlands.h"

#include "Battlefield.h"
#include "Location.h"
#include "prototypes.h"

#include "BackendCommand.h"
#include "LocalMapCommand.h"
#include "NextLocationCommand.h"
#include "BuySellCommand.h"
#include "FightEndTurnCommand.h"

#include "DemoNextLocationCommand.h"

// #include "FrontendCommand.h"
// list of other frontend commands here

#include "Playground.h"
#include "Forge.h"

#include <vector>

class World {
  public:
    World(char* name);
    virtual ~World();
    int render();
    
    Playground* _playground;
    
    std::vector<BackendCommand*> _backend_query;
    // std::vector<FrontendCommand*> _input_query;
    // std::vector<FrontendCommand*> _output_query;
};

// to Valeriy: link your Irrlicht-related code with this class,
// _input_query is for commands generated by user input,
// _output_query is for graphics output commands (make class FrontendCommand derived from command and derive other classes from it)

// render() method is for game loop, it executes commands in this sequence: first, user input query, then backend commands query and graphics output afterall
// iterations of game loop must be on constant frequency

#endif
