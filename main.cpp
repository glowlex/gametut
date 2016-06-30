#pragma once
#include <irrlicht.h>
#include <driverChoice.h>
#include <stdlib.h>     
#include <time.h>    
#include <irrString.h>
#include <vector>
#include "field.h"
#include "FieldInterface.h"
#include "field.cpp"
#include "FieldInterface.cpp"
#include "conf.h"
#include <cstdio>

/*
#include "source\polymorph\World.h"
#include "source\polymorph\World.cpp"*/


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#pragma comment(lib, "Irrlicht.lib")

s32 shaderMaterialType;

Field field;


IrrlichtDevice* device = 0;
bool UseHighLevelShaders = true;



int main()
{
    g_screen_width = 1280;
    g_screen_height = 720;
    IrrlichtDevice* device = field.initDevice();
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* env = device->getGUIEnvironment();


/*
    MainMenuEventReceiver* receiver1 = new MainMenuEventReceiver;
    device->setEventReceiver(receiver1);
    field.initMainMenu();
    field.drawMainMenu(); //в целях теста закоменчено.
    if (g_quit_game) {
        return 0;
    }*/

/*
    char* g = "ggg";

    World* world = new World(g);*/



    field.initTerrain();
    env->addStaticText(
        L"Press 'W' to change wireframe mode\nPress 'D' to toggle detail map\nPress 'S' to toggle skybox/skydome",
        core::rect<s32>(10, 421, 250, 475), true, true, 0, -1, true);
    //interface

    field.initInterface();
    FieldInterface* receiver = new FieldInterface(&field);
    device->setEventReceiver(receiver);


    //test
    scene::ISceneNode* highlightedSceneNode = 0;
    scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
    //test{
    IMeshSceneNode* mynode;
    ISceneNode* pic;
    field.setUnits(field.terrain);
    mynode = smgr->addCubeSceneNode(CELLSIZE);
    mynode->setMaterialTexture(0, driver->getTexture("../gametut/media/wall.jpg"));
    mynode->setPosition(core::vector3df(0.f, 0.f, 0.f));
    mynode->setMaterialFlag(video::EMF_LIGHTING, false);
   // pic = smgr->addBillboardSceneNode(mynode, dimension2d<f32>(350.f, 350.f), vector3df(0, CELLSIZE, 0));
    //pic->setMaterialFlag(EMF_LIGHTING, false);
    //pic->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
    //video::ITexture* images = driver->getTexture("../gametut/media/1.bmp");
    //driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
    //pic->setMaterialTexture(0, images);

    u32 then = device->getTimer()->getTime();


    //test}
    int lastFPS = -1;

    while (device->run())
    if (device->isWindowActive())
    {
        u32 now = device->getTimer()->getTime();
        f32 frameDeltaTime = (f32)(now - then) / 1000.f; // в секундах
        then = now;
        if (field.isUnitOnMove()) {
            field.moveUnit(frameDeltaTime);
        }
        driver->beginScene(true, true, 0);
        //vector3df g = field.camera->getRotation();
        smgr->drawAll();
        env->drawAll();


        line3d<f32> ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(receiver->MouseState.position);
        core::vector3df intersection;
        core::triangle3df hitTriangle;
        scene::ISceneNode * selectedSceneNode =
            collMan->getSceneNodeAndCollisionPointFromRay(
            ray,
            intersection,
            hitTriangle,
            0,
            0);
        if (selectedSceneNode) {
            receiver->setSelectedSceneNode(selectedSceneNode);
            printf("%d  ", selectedSceneNode->getID());
        }

        if (!field.isUnitOnMove()){
            field.setSelectedCell(intersection);
        }
        driver->draw3DTriangle(hitTriangle, video::SColor(0, 255, 0, 0));

        video::SMaterial material;
        if (selectedSceneNode)
        {

            driver->setTransform(video::ETS_WORLD, core::matrix4());

            driver->setMaterial(material);
/*
            if (field.getSelectedCell() == NULL) {
                mynode->setVisible(true);
                mynode->setPosition(field.selectedCellf);
            }
            else {
                mynode->setVisible(false);
            }*/


           // driver->setTransform(video::ETS_WORLD, core::matrix4());
            //driver->draw3DTriangle(hitTriangle, video::SColor(0, 255, 0, 0));

            // We can check the flags for the scene node that was hit to see if it should be
            // highlighted. The animated nodes can be highlighted, but not the Quake level mesh
            if ((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
            {
                highlightedSceneNode = selectedSceneNode;
                //highlightedSceneNode->setPosition(intersection);
            }
        }
        driver->endScene();

        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw str = L"Terrain Renderer - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
            str += " Height: ";
            str += field.terrain->getHeight(field.camera->getAbsolutePosition().X,
                field.camera->getAbsolutePosition().Z);

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }//draw fps        // display frames per second in window title
    }

    device->drop();

    return 0;
}
