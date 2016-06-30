
#include "field.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum
{
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
    IDFlag_IsHighlightable = 1 << 1
};

void cShaderCallback::OnSetConstants(video::IMaterialRendererServices* services,
        s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();
        // set clip matrix
        core::matrix4 worldViewProj;
        worldViewProj = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);
        // worldViewProj.makeInverse();
        // if (UseHighLevelShaders)
        services->setVertexShaderConstant("matViewProjection", worldViewProj.pointer(), 16);
        //  else
        // services->setVertexShaderConstant(worldViewProj.pointer(), 4, 4);
        s32 TextureLayerID = 0;
        services->setPixelShaderConstant("mask", &TextureLayerID, 1);
        s32 TextureLayerID1 = 1;
        services->setPixelShaderConstant("layer1", &TextureLayerID1, 1);
        s32 TextureLayerID2 = 2;
        services->setPixelShaderConstant("layer2", &TextureLayerID2, 1);
        s32 TextureLayerID3 = 3;
        services->setPixelShaderConstant("layer3", &TextureLayerID3, 1);
        s32 TextureLayerID4 = 4;
        services->setPixelShaderConstant("layer4", &TextureLayerID4, 1);
        s32 TextureLayerID5 = 5;
        services->setPixelShaderConstant("grid", &TextureLayerID5, 1);


    }



    Field::Field(){
        selectedUnit = vector3di(0, 0, 0);
        selectedCell = vector3di(0, 0, 0); //клетка с наведённым курсором
        unitPicked = false;
        unitOnMove = false;
        for (int i = 0; i < FILDSIZE; i++)
        for (int j = 0; j < FILDSIZE; j++)
        {
            fieldCells[i][j] = NULL;
        }
        //test

    }
    IrrlichtDevice* Field::initDevice() {
        video::E_DRIVER_TYPE driverType = EDT_OPENGL;
        // if (driverType == video::EDT_COUNT)
        // return 1;

        irr::SIrrlichtCreationParameters params;
        params.DriverType = driverType;
        params.WindowSize = core::dimension2d<u32>(g_screen_width, g_screen_height);
        device = createDeviceEx(params);

        //if (device == 0)
        //  return 1;
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        env = device->getGUIEnvironment();

        driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

        env->getSkin()->setFont(env->getFont("D:/Documents/Visual Studio 2013/Projects/repo2016/gametut/gametut/media/fontlucida.png"));

        return device;
    }

    void Field::initTerrain() {
        //todo call for textures
        std::vector<ITexture*> mask, textures;
        mask.push_back(driver->getTexture("../gametut/media/Sample.bmp"));
        textures.push_back(driver->getTexture("../gametut/media/sandstone.jpg"));
        textures.push_back(driver->getTexture("../gametut/media/grass_1.jpg"));
        textures.push_back(driver->getTexture("../gametut/media/SANDSHOR.JPG"));
        textures.push_back(driver->getTexture("../gametut/media/water (2).jpg"));
        //ITexture* fieldTexture = makeTerrainTexure(mask, textures);
        terrain = smgr->addTerrainSceneNode(
            "D:/Documents/Visual Studio 2013/Projects/repo2016/gametut/gametut/media/heightmap_1x1.jpg", // terrain-heightmap.bmp
            0,					// parent node
            -1,					// node id
            core::vector3df(0.f, 0.f, 0.f),		// position
            core::vector3df(0.f, 0.f, 0.f),		// rotation
            core::vector3df(40.f, 4.4f, 40.f),	// scale
            video::SColor(255, 255, 255, 255),	// vertexColor
            5,					// maxLOD
            scene::ETPS_17,				// patchSize
            4					// smoothFactor
            );

        vector3df tercent = terrain->getTerrainCenter();
        camera =
            smgr->addCameraSceneNodeMaya(0, 100.0f, 1.2f);

        camera->setPosition(tercent + core::vector3df(0, 2500, 0));
        camera->setTarget(tercent + core::vector3df(100, 500, 0));
        camera->setFarValue(62000.0f);
        terrain->setMaterialFlag(video::EMF_LIGHTING, false);

        scene::ITriangleSelector* selector
            = smgr->createTerrainTriangleSelector(terrain, 0);
        terrain->setTriangleSelector(selector);

        // create collision response animator and attach it to the camera
        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, camera, core::vector3df(60, 100, 60),
            core::vector3df(0, 0, 0),
            core::vector3df(0, 50, 0));
        selector->drop();
        camera->addAnimator(anim);
        anim->drop();

        driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

        skybox = smgr->addSkyBoxSceneNode(
            driver->getTexture("../gametut/media/irrlicht2_up.jpg"),
            driver->getTexture("../gametut/media/irrlicht2_dn.jpg"),
            driver->getTexture("../gametut/media/irrlicht2_lf.jpg"),
            driver->getTexture("../gametut/media/irrlicht2_rt.jpg"),
            driver->getTexture("../gametut/media/irrlicht2_ft.jpg"),
            driver->getTexture("../gametut/media/irrlicht2_bk.jpg"));
        skydome = smgr->addSkyDomeSceneNode(driver->getTexture("../gametut/media/skydome.jpg"), 16, 8, 0.95f, 2.0f);

        driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

        io::path vs_main = "../gametut/media/opengl.vert";
        io::path ps_main = "../gametut/media/opengl.frag";
        if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_2_0))
        {
            device->getLogger()->log("WARNING: Pixel shaders disabled "\
                "because of missing driver/hardware support.");
            ps_main = "";
        }

        if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_2_0))
        {
            device->getLogger()->log("WARNING: Vertex shaders disabled "\
                "because of missing driver/hardware support.");
            vs_main = "";
        }

        IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
        cShaderCallback* sC = new cShaderCallback();
        s32 shaderMaterialType = gpu->addHighLevelShaderMaterialFromFiles(
            vs_main, "vs_main", video::EVST_VS_2_0,
            ps_main, "ps_main", video::EPST_PS_2_0,
            sC, video::EMT_DETAIL_MAP);

        int i = 0;
        terrain->setMaterialTexture(0, mask[0]);
        terrain->setMaterialTexture(1, textures[i++]);
        terrain->setMaterialTexture(2, textures[i++]);
        terrain->setMaterialTexture(3, textures[i++]);
        terrain->setMaterialTexture(4, textures[i++]);
        terrain->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterialType);
        terrain->scaleTexture(1.0f, 20.0f);
        // terrain->setMaterialTexture(0, fieldTexture);
        // terrain->setMaterialType(video::EMT_SOLID);
        smgr->setActiveCamera(camera);
    }

    void Field::initInterface() {
        IGUISkin* skin = env->getSkin();
        IGUIFont* font = env->getFont("../gametut/media/myfont+10.xml");
        if (font)
            skin->setFont(font);

        skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
/*

        for (u32 i = 0; i < EGDC_COUNT; ++i)
        {
            SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
            col.setAlpha(254);
            skin->setColor((EGUI_DEFAULT_COLOR)i, col);
        }*/

        env->addButton(rect<s32>(DEFAULT_MARGIN, DEFAULT_MARGIN, DEFAULT_BUTTON_WIDTH + DEFAULT_MARGIN, DEFAULT_MARGIN + DEFAULT_BUTTON_HEIGHT),
            0, GUI_ID_QUIT_BUTTON,
            L"Quit", L"Exits Program");
        env->addButton(rect<s32>(g_screen_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, DEFAULT_MARGIN,
            g_screen_width - DEFAULT_MARGIN, DEFAULT_MARGIN + DEFAULT_BUTTON_HEIGHT)
            , 0, GUI_ID_OPEN_INVENTORY,
            L"Inventory", L"Launches a new Window");
        env->addButton(rect<s32>(g_screen_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, g_screen_height*0.5,
            g_screen_width - DEFAULT_MARGIN, g_screen_height*0.5 + DEFAULT_BUTTON_HEIGHT), 0, GUI_ID_ENDTURN_BUTTON,
            L"End Turn", L"Ends Turn");

        env->addButton(rect<s32>(g_screen_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, DEFAULT_MARGIN+200,
            g_screen_width - DEFAULT_MARGIN, DEFAULT_MARGIN + DEFAULT_BUTTON_HEIGHT+200)
            , 0, GUI_ID_END_BATTLE_NEXT_BUTTON,
            L"endbattle", L"Launches a new Window");
        env->addButton(rect<s32>(g_screen_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, DEFAULT_MARGIN + 300,
            g_screen_width - DEFAULT_MARGIN, DEFAULT_MARGIN + DEFAULT_BUTTON_HEIGHT + 300)
            , 0, GUI_ID_EQUIP_BUTTON,
            L"equip", L"Launches a new Window");

        env->addButton(rect<s32>(g_screen_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, DEFAULT_MARGIN + 100,
            g_screen_width - DEFAULT_MARGIN, DEFAULT_MARGIN + DEFAULT_BUTTON_HEIGHT + 100)
            , 0, GUI_ID_SQUAD_BUTTON,
            L"squad", L"Launches a new Window");

        //env->addStaticText(L"Logging ListBox:", rect< s32 >(50, 110, 250, 130), true);
        //IGUIListBox * listbox = env->addListBox(rect< s32 >(50, 140, 250, 210));
        //env->addEditBox(L"Editable Text", rect< s32 >(350, 80, 550, 100));

        // Создаем структуру, которую передадим в наш
        // обработчик событий для обратной связи с движком
        context;
        context.device = device;
        context.counter = 0;
        //context.listbox = listbox;
    }

    void Field::setDevice(IrrlichtDevice* device) {
        this->device = device;
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        env = device->getGUIEnvironment();

    }
    void Field::endMove() {
        if (unitOnMove) {
            getSelectedUnit()->node->setPosition(selectedCellf);
            fieldCells[selectedCell.X][selectedCell.Z] = getSelectedUnit();
            fieldCells[selectedUnit.X][selectedUnit.Z] = NULL;
            unitOnMove = false;
            unitPicked = false;
        }
    }
    bool Field::isUnitOnMove(){
        return unitOnMove;
    }
    bool Field::isUnitSelected(){
        return unitPicked;
    }
    void Field::moveUnit(f32 &frameDeltaTime){
        vector3df nextpos;
        vector3df curpos = getSelectedUnit()->node->getPosition();
        const f32 availableMovement = frameDeltaTime * MOVEMENT_SPEED;
        if ((selectedCellf - curpos).getLength() <= availableMovement) {
            nextpos = selectedCellf;
            getSelectedUnit()->node->setPosition(nextpos);
            endMove();
            return;
        }
        else {
            nextpos = curpos + (selectedCellf - curpos + vector3df(0, abs(selectedCellf.X - curpos.X) + abs(selectedCellf.Z - curpos.Z) < 1000 ?
                abs(selectedCellf.X - curpos.X) + abs(selectedCellf.Z - curpos.Z) : 1000
                , 0)).normalize()*availableMovement;
        }
        getSelectedUnit()->node->setPosition(nextpos);
    }
    void Field::setUnitOnMove() {
        unitOnMove = true;

    }
    void Field::selectUnit(scene::ISceneNode* selectedSceneNode){
        //TODO иную обработку выбора юнита по мешу
        if (unitPicked) {
            if (getSelectedCell() == NULL) {
                setUnitOnMove();
            }
            else {
                selectedUnit = selectedCell;
            }
        }
        else if (getSelectedCell() != NULL) {
            unitPicked = true;
            selectedUnit = selectedCell;
        }

    }
    void Field::addUnit(vector3di pos, IMeshSceneNode* node) {
        if (getCell(pos) == NULL) {
            fieldCells[pos.X][pos.Z] = new unit(node->getID());
        }
        getCell(pos)->node = node;
    }
    unit* Field::getSelectedUnit() {
        return fieldCells[selectedUnit.X][selectedUnit.Z];
    }
    unit* Field::getCell(vector3di a){
        return fieldCells[a.X][a.Z];
    }
    unit* Field::getSelectedCell(){
        return fieldCells[selectedCell.X][selectedCell.Z];
    }
    void Field::setSelectedCell(vector3df a) {
        //корректируем по границам клетки и добавляем 0.5 размера клетки для удобного  перекла мажду клетками
        selectedCellf = vector3df((selectedCell.X = int((a.X + CELLSIZE / 2) / CELLSIZE))*CELLSIZE, int((a.Y + CELLSIZE / 2) / CELLSIZE)*CELLSIZE,
            (selectedCell.Z = int((a.Z + CELLSIZE / 2) / CELLSIZE))*CELLSIZE);
    }
    void Field::setUnits(scene::ITerrainSceneNode* terrain) {
        IMeshSceneNode* mynode;
        ISceneNode* pic;
        srand(time(NULL));
        int id = 1000;
        for (int i = 0; i < FILDSIZE - 1; i++)
        for (int j = 0; j < FILDSIZE - 1; j++)
        {
             
            if (!(i % 6) && j % 2){
                mynode = smgr->addCubeSceneNode(CELLSIZE, 0, id++);
                mynode->setPosition(vector3df(i * CELLSIZE, terrain->getHeight(i * CELLSIZE, j * CELLSIZE), j * CELLSIZE));
                mynode->setMaterialFlag(video::EMF_LIGHTING, false);
                mynode->setMaterialTexture(0, driver->getTexture(L"../gametut/media/wall.jpg"));
                mynode->setMaterialTexture(1, driver->getTexture(L"../gametut/media/stones.jpg"));
                mynode->setMaterialFlag(video::EMF_BLEND_OPERATION, true);
                ITriangleSelector* selector = smgr->createTriangleSelector(mynode->getMesh(), mynode);
                mynode->setTriangleSelector(selector);
                selector->drop(); // селектор более не нужен - дропаем.
                //mynode->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterialType);
                this->addUnit(vector3di(i, 0, j), mynode);

                pic = smgr->addBillboardSceneNode(mynode, dimension2d<f32>(350.f, 350.f), vector3df(0, CELLSIZE, 0));
                pic->setMaterialFlag(EMF_LIGHTING, false);
                pic->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
                irr::core::stringw s = stringw(PATH_UNIT_MODEL) + stringw((rand() % 7) + 1) + stringw(L".jpg");

                video::ITexture* images = driver->getTexture(s.c_str());
                driver->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
                pic->setMaterialTexture(0, images);
            }
        }
    }

ITexture* Field::makeTerrainTexure(std::vector<ITexture*> mask, std::vector<ITexture*> textures) {

    scene::ITerrainSceneNode* terrain1 = smgr->addTerrainSceneNode(
        "D:/Documents/Visual Studio 2013/Projects/repo2016/gametut/gametut/media/heightmap.jpg", // terrain-heightmap.bmp
        0,					// parent node
        -1,					// node id
        core::vector3df(0.f, 0.f, 0.f),		// position
        core::vector3df(0.f, 90.f, 0.f),		// rotation
        core::vector3df(40.f, 4.4f, 40.f),	// scale
        video::SColor(255, 255, 255, 255),	// vertexColor
        5,					// maxLOD
        scene::ETPS_17,				// patchSize
        4					// smoothFactor
        );
    vector3df tercent = terrain1->getTerrainCenter();
    //fixedCam = smgr->addCameraSceneNode(0, tercent + core::vector3df(0, 100, 0), core::vector3df(-10, 10, -100));
    scene::ICameraSceneNode* camera1 =
        smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
    camera1->setPosition(tercent + core::vector3df(0, 3500, 0)); //было 6500 потом перестало работать норм
    camera1->setTarget(tercent);
    camera1->setFarValue(62000.0f);
    terrain1->setMaterialFlag(video::EMF_LIGHTING, false);

    io::path vs_main = "../gametut/media/opengl.vert";
    io::path ps_main = "../gametut/media/opengl.frag";
    IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
    cShaderCallback* sC = new cShaderCallback();
    s32 shaderMaterialType = gpu->addHighLevelShaderMaterialFromFiles(
        vs_main, "vs_main", video::EVST_VS_2_0,
        ps_main, "ps_main", video::EPST_PS_2_0,
        sC, video::EMT_DETAIL_MAP);

    terrain1->scaleTexture(1.0f, 20.0f);
    int i = 0;
    terrain1->setMaterialTexture(0, mask[0]);
    terrain1->setMaterialTexture(1, textures[i++]);
    terrain1->setMaterialTexture(2, textures[i++]);
    terrain1->setMaterialTexture(3, textures[i++]);
    terrain1->setMaterialTexture(4, textures[i++]);
    terrain1->setMaterialType((video::E_MATERIAL_TYPE)shaderMaterialType);
    ITexture* res = driver->addRenderTargetTexture(core::dimension2d<u32>(10240, 10240),
        "RTT1");
    device->run();
    driver->beginScene(true, true, 0);
    driver->setRenderTarget(res, true, true, video::SColor(0, 0, 0, 255));
    // рисуем всю сцену на "полотно"
    smgr->drawAll();
    driver->setRenderTarget(0, true, true, 0);
    terrain1->remove();
    return res;
}


void Field::initMainMenu() {
    IGUISkin* skin = env->getSkin();
    IGUIFont* font = env->getFont("../gametut/media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
    IGUIImage* img = env->addImage(rect<s32>(0, 0, g_screen_width, g_screen_height));
    img->setScaleImage(true);
    img->setImage(driver->getTexture("../gametut/media/main_menu.jpg"));
    env->addButton(rect<s32>(g_screen_width*0.5 - DEFAULT_BUTTON_WIDTH*0.5, g_screen_height*0.5 - DEFAULT_BUTTON_HEIGHT*0.5,
        g_screen_width*0.5 + DEFAULT_BUTTON_WIDTH*0.5, g_screen_height*0.5 + DEFAULT_BUTTON_HEIGHT*0.5),
        0, GUI_ID_START_GAME_BUTTON,
        L"START!", L"START!!!");

    env->addButton(rect<s32>(g_screen_width*0.5 - DEFAULT_BUTTON_WIDTH*0.5, g_screen_height*0.5 + DEFAULT_BUTTON_HEIGHT*0.5+DEFAULT_MARGIN*2,
        g_screen_width*0.5 + DEFAULT_BUTTON_WIDTH*0.5, g_screen_height*0.5 + DEFAULT_BUTTON_HEIGHT*1.5 + DEFAULT_MARGIN * 2),
        0, GUI_ID_LOAD_GAME_BUTTON,
        L"Load", L"Load!");

    env->addButton(rect<s32>(g_screen_width*0.5 - DEFAULT_BUTTON_WIDTH*0.5, g_screen_height - DEFAULT_MARGIN - DEFAULT_BUTTON_HEIGHT,
        g_screen_width*0.5 + DEFAULT_BUTTON_WIDTH*0.5, g_screen_height - DEFAULT_MARGIN),
        0, GUI_ID_QUIT_BUTTON,
        L"Quit!", L"Quit nahoy!");
}

void Field::drawMainMenu() {
    while (!g_start_game && !g_quit_game && device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(255, 0, 0, 0));
            smgr->drawAll();
            env->drawAll();
            driver->endScene();
        }
    }
    env->clear();
}