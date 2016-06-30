#ifndef FIELDINTERFACE_H
#define FIELDINTERFACE_H

#pragma once

#include <irrlicht.h>
#include <driverChoice.h>
#include <stdlib.h>     
#include <time.h>    
#include <irrString.h>
#include <vector>
#include "field.h"
#include <cstdio>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class MainMenuEventReceiver : public IEventReceiver, public Field
{
public:
    bool OnEvent(const SEvent& event);
};


class FieldInterface : public IEventReceiver, public Field
{
public:
    struct SMouseState
    {
        core::position2di position;
        position2d<s32> clickPosition;
        bool leftButtonDown;
        bool leftButtonDownMove;
        SMouseState() : leftButtonDown(false), leftButtonDownMove(false) { }
    } MouseState;
    FieldInterface(Field* field);

    bool OnEvent(const SEvent& event);
    void showOpenInventory(std::vector<stringw*>* items, s32 x = INVENTORY_WINDOW_POS_X, s32 y = INVENTORY_WINDOW_POS_Y, s32 width = INVENTORY_WINDOW_WIDTH,
        s32 height = INVENTORY_WINDOW_HEIGHT,  IGUIElement* parrent = (IGUIElement *)0);
    void showUnitInfo( stringw* units, s32 x, s32 y);
    void setSelectedSceneNode(scene::ISceneNode* s);
    void fillGUIFields(IGUIElement* n, stringw* str);
    void showEndBattleWindow(std::vector<stringw*>* items, std::vector<stringw*>* trophys, s32 x = END_BATTLE_WINDOW_POS_X, s32 y = END_BATTLE_WINDOW_POS_Y);
    void showItemInfo(stringw* item, s32 x, s32 y, s32 width = ITEM_INFO_WINDOW_WIDTH, s32 height = ITEM_INFO_WINDOW_HEIGHT,  IGUIElement* parrent = (IGUIElement *)0, s32 id = -1);
    void showEquipWindow(std::vector<stringw*>* items, s32 x, s32 y, s32 width = EQUIP_INFO_WINDOW_WIDTH, s32 height = EQUIP_INFO_WINDOW_HEIGHT, IGUIElement* parrent = (IGUIElement *)0, s32 id = -1);
    void showSquadWindow(std::vector<stringw*>* units);
    rect<s32> getRectPopupWindow(core::position2di pos, s32 width, s32 height);
    rect<s32> getRectWindow(s32 x, s32 y, s32 width, s32 height);
    void testfill();
private:
    Field* field;
    s32 selectedUnit;
    std::vector<stringw*>* inventory_items;
    std::vector<stringw*>* inventory_prophy_items;
    std::vector<stringw*>* squad_units;
    gui::IGUIEnvironment* env;
    scene::ISceneNode* terrain;
    scene::ISceneNode* skybox;
    scene::ISceneNode* skydome;
    IGUIStaticText* inventoryStaticText;
    scene::ISceneNode* selectedSceneNode;
    bool showBox;
    bool showDebug;
    s32 lastUnitId;
    SAppContext & Context;
};

#endif