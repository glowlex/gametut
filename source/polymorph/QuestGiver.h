#pragma once

#ifndef QUESTGIVER_H
#define QUESTGIVER_H

#include "NPC.h"
#include "prototypes.h"

class QuestGiver : public NPC {
  public:
    QuestGiver(): NPC() { _quest_id = FREE_INDEX; }
    QuestGiver(TNPCPrototype &prototype, int level): NPC() { _quest_id = FREE_INDEX; }
    virtual ~QuestGiver() {}
    
    int get_quest_id() { return _quest_id; }
    int speak(unsigned char* &out) { return 0;}
    int what(std::string &out) { return 0;}

  protected:
    int _quest_id;
};

#endif
