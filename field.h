#ifndef FIELD_H
#define FIELD_H

#pragma once

#include <irrlicht.h>
#include <driverChoice.h>
#include <stdlib.h>
#include <time.h>
#include <irrString.h>
#include <vector>
#include "conf.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class cShaderCallback : public video::IShaderConstantSetCallBack
{
public:
    virtual void OnSetConstants(video::IMaterialRendererServices* services,
        s32 userData);
};

struct unit
{
    s32 a;
    s32 id;
    IMeshSceneNode* node;
    unit(s32 id) :id(id){}
};

struct SAppContext
{
    IrrlichtDevice *device; // указатель на корневой объект
    s32 counter; // счетчик
    IGUIListBox* listbox; // указатель на GUI элемент - список
};

class Field {
public:
    IrrlichtDevice* device;
    video::IVideoDriver* driver;
    scene::ISceneManager* smgr;
    gui::IGUIEnvironment* env;
    scene::ITerrainSceneNode* terrain;
    scene::ISceneNode* skybox;
    scene::ISceneNode* skydome;
    scene::ICameraSceneNode* camera;
    SAppContext context;
    vector3df selectedCellf;
    vector3di selectedCell;
    unit* fieldCells[FILDSIZE][FILDSIZE];
    bool unitPicked;
    bool unitOnMove;
    vector3di selectedUnit;
    Field();
    ITexture* makeTerrainTexure(std::vector<ITexture*> mask, std::vector<ITexture*> textures);
    IrrlichtDevice* initDevice();

    void initTerrain();
    void initMainMenu();
    void drawMainMenu();

    void initInterface();

    void setDevice(IrrlichtDevice* device);
    void endMove();
    bool isUnitOnMove();
    bool isUnitSelected();
    void moveUnit(f32 &frameDeltaTime);
    void setUnitOnMove();
    void selectUnit(scene::ISceneNode* selectedSceneNode);
    void addUnit(vector3di pos, IMeshSceneNode* node);
    unit* getSelectedUnit();
    unit* getCell(vector3di a);
    unit* getSelectedCell();
    void setSelectedCell(vector3df a);
    void setUnits(scene::ITerrainSceneNode* terrain);
};


#endif
