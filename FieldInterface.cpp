
#include "FieldInterface.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



bool MainMenuEventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
        case EGET_BUTTON_CLICKED:
            switch (id)
            {

            case GUI_ID_LOAD_GAME_BUTTON:
                //todo load game
                return true;

            case GUI_ID_QUIT_BUTTON:
                g_quit_game = true;
                return true;
            case GUI_ID_START_GAME_BUTTON:
                g_start_game = true;
                break;

            default:
                return false;
            }
            break;

        default:
            break;
        }
    }
    return false;

}

FieldInterface::FieldInterface(Field* field) :
terrain(field->terrain), skybox(field->skybox), skydome(field->skydome), showBox(true), showDebug(false), Context(field->context),
field(field), env(field->env), selectedSceneNode(NULL)
{
    testfill();
    skybox->setVisible(showBox);
    skydome->setVisible(!showBox);
}

bool FieldInterface::OnEvent(const SEvent& event)
{

    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        if (!field->isUnitOnMove()) {
            s32 curid = NULL;
            //IGUIElement* focuselem = env->getFocus();
            switch (event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.clickPosition.X = event.MouseInput.X;
                MouseState.clickPosition.Y = event.MouseInput.Y;

                MouseState.leftButtonDownMove = true;
                MouseState.leftButtonDown = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.clickPosition.X = event.MouseInput.X;
                MouseState.clickPosition.Y = event.MouseInput.Y;
                field->selectUnit(selectedSceneNode);
                MouseState.leftButtonDownMove = false;
                MouseState.leftButtonDown = false;
                break;

            case EMIE_MOUSE_MOVED:
/*
                //посылает клик при наведении на листбокс для всплывания описания
                if (focuselem && focuselem->getType() == EGUIET_LIST_BOX) {
                    SEvent gg;
                    gg.EventType = irr::EET_MOUSE_INPUT_EVENT;
                    gg.MouseInput.Event = EMIE_LMOUSE_PRESSED_DOWN;
                    env->postEventFromUser(gg);
                    printf("click ");
                }*/

                MouseState.position.X = event.MouseInput.X;
                MouseState.position.Y = event.MouseInput.Y;
                if (MouseState.leftButtonDown) {
                    break;
                }
                if (selectedSceneNode){
                    curid = selectedSceneNode->getID();
                }


                if ((!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_USERINFO_WINDOW)) && curid != -1) {
                    if (curid >= 1000){
                        showUnitInfo((*squad_units)[curid - 1000], MouseState.position.X, MouseState.position.Y);
                }
                    lastUnitId = curid;
                }
                else if (lastUnitId != curid || curid == -1){
                    IGUIElement* e = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_USERINFO_WINDOW);
                    if (e) {
                        e->remove();
                    }
                }
                break;

            default:
                // We won't use the wheel
                break;
            }
        }
    }

    // check if user presses the key 'W' or 'D'
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
    {
        switch (event.KeyInput.Key)
        {
        case BUTTON_ID_SKIP_UNIT_MOVE:
            if (field->isUnitOnMove()) {
                field->endMove();
            }
/* //todo пипа пробелом перемещать в конце боя
            else if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)) {
                SEvent gg;
                gg.EventType = irr::EET_GUI_EVENT;
                gg.GUIEvent.EventType = EGET_BUTTON_CLICKED;
                gg.GUIEvent.Caller = env->getRootGUIElement()->getElementFromId(GUI_ID_END_BATTLE_TAKE_ITEM_BUTTON, true);
                env->postEventFromUser(gg);
            }*/
            return true;

        case irr::KEY_KEY_W: // switch wire frame mode
            terrain->setMaterialFlag(video::EMF_WIREFRAME,
                !terrain->getMaterial(0).Wireframe);
            terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
            return true;
        case irr::KEY_KEY_P: // switch wire frame mode
            terrain->setMaterialFlag(video::EMF_POINTCLOUD,
                !terrain->getMaterial(0).PointCloud);
            terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
            return true;
        case irr::KEY_KEY_D: // toggle detail map
            /*
                            Terrain->setMaterialType(
                            Terrain->getMaterial(0).MaterialType == video::EMT_SOLID ?
                            (video::E_MATERIAL_TYPE)shaderMaterialType : video::EMT_SOLID);*/
            return true;
        case irr::KEY_KEY_S:
            showBox = !showBox;
            skybox->setVisible(showBox);
            skydome->setVisible(!showBox);
            return true;
        case irr::KEY_KEY_X:
            showDebug = !showDebug;
            terrain->setDebugDataVisible(showDebug ? scene::EDS_BBOX_ALL : scene::EDS_OFF);
            return true;
        default:
            break;
        }
    }

    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();
        switch (event.GUIEvent.EventType)
        {
        case EGET_BUTTON_CLICKED:
            if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW, true) && event.GUIEvent.Caller->getParent() != env->getRootGUIElement()
                && event.GUIEvent.Caller->getParent()->getParent()->getID() == CHECK_GUI_ID_EQUIP_WINDOW) {
                irr::core::stringc name = event.GUIEvent.Caller->getName();
                if /*(name == "Head")*/ (event.GUIEvent.Caller->getID() == HEAD)
                {
                    IGUIElement* par = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW, true);
                    rect<s32> pos = par->getAbsolutePosition();

                    if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_ITEM_INFO, true)){
                        env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_ITEM_INFO, true)->remove();
                    }
                    showItemInfo((*inventory_items)[id], pos.UpperLeftCorner.X + pos.getWidth(), pos.UpperLeftCorner.Y, ITEM_INFO_WINDOW_WIDTH,
                        ITEM_INFO_WINDOW_HEIGHT,  env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW, true), CHECK_GUI_ID_EQUIP_ITEM_INFO);
                }
                else{


                    return true;
                }
            } else if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW, true) && event.GUIEvent.Caller->getParent() != env->getRootGUIElement()
                    && event.GUIEvent.Caller->getParent()->getID() == CHECK_GUI_ID_SQUAD_WINDOW) {
                    s32 id  = event.GUIEvent.Caller->getID();
                    IGUIElement* par = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW, true);
                    rect<s32> pos = par->getAbsolutePosition();
                    if (id < 100) {
                        if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW, true)){
                            env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW, true)->remove();
                        }
                        showEquipWindow(inventory_items, 0, SCREEN_HEIGHT / 2 - DEFAULT_MARGIN, (SCREEN_HEIGHT / 2) * 3 / 4, SCREEN_HEIGHT / 2,
                            env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW, true), CHECK_GUI_ID_EQUIP_WINDOW);
                    }

                }

            switch (id)
            {
            case GUI_ID_END_BATTLE_TAKE_ITEM_BUTTON:
                // todo перемещение трофеев в инвентарь.
                if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)) {
                    IGUIElement* tl = (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_LISTBOXL_WINDOW, true)->getParent()->getParent());
                    s32 dl = ((IGUITabControl*)tl)->getActiveTab();
                    IGUIElement* ll = ((IGUITabControl*)tl)->getTab(dl);
                    IGUIListBox* listl = (IGUIListBox*)(*(ll->getChildren().begin()));

                    IGUIElement* tr = (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_LISTBOXR_WINDOW, true)->getParent()->getParent());
                    s32 dr = ((IGUITabControl*)tr)->getActiveTab();
                    IGUIElement* lr = ((IGUITabControl*)tr)->getTab(dr);
                    IGUIListBox* listr = (IGUIListBox*)(*(lr->getChildren().begin()));

                    if (listl && listr) {
                        if (listl->getSelected() != -1) {
                            listr->addItem(listl->getListItem(listl->getSelected()));
                            inventory_items->push_back((*inventory_prophy_items)[listl->getSelected()]);
                            inventory_prophy_items->erase(inventory_prophy_items->begin() + listl->getSelected());
                            s32 n = listl->getSelected();
                            listl->removeItem(n);
                            listl->setSelected(n);

                        }
                    }
                }
                return true;

            case GUI_ID_QUIT_BUTTON:
                Context.device->closeDevice();
                return true;

            case GUI_ID_EQUIP_BUTTON:
                if (!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW)){
                    showEquipWindow(inventory_items, 100, 100);
                }
                else {
                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_EQUIP_WINDOW)->remove();
                }
                return true;

            case GUI_ID_OPEN_INVENTORY:
                if (!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)) {
                    //showOpenInventory(MouseState.position.X, MouseState.position.Y);
                    showOpenInventory(inventory_items, END_BATTLE_WINDOW_POS_X, END_BATTLE_WINDOW_POS_Y, INVENTORY_WINDOW_WIDTH, INVENTORY_WINDOW_HEIGHT);
                }
                else {
                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)->remove();
                    if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)){
                        env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)->remove();
                    }
                }
                return true;

            case GUI_ID_ENDTURN_BUTTON:
                //todo send to backend
                return true;
            case GUI_ID_INVENTORY_EQUIP_BUTTON:
                //todo send backend
                return true;
            case GUI_ID_END_BATTLE_TAKE_ALL_BUTTON:
                // todo take all
                //test
/*
                if (!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)) {
                    showOpenInventory(MouseState.position.X, MouseState.position.Y);
                }
                else {
                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)->remove();
                }*/
                return true;
            case  GUI_ID_END_BATTLE_NEXT_BUTTON:
                // todo next
                //test
                if (!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW)) {
                    showEndBattleWindow(inventory_items, inventory_prophy_items);
                }
                else {
                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW)->remove();
                }
                return true;
            case GUI_ID_SQUAD_BUTTON:
                if (!env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW)) {
                    showSquadWindow(squad_units);
                }
                return true;

            case GUI_ID_EQUIP_CLOSE_BUTTON:
                if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW)) {
                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW)->remove();
                    if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_ITEM_INFO)){
                        env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_ITEM_INFO)->remove();
                    }
                    if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)){
                        env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW)->remove();
                    }
                }
                return true;


            default:
                return false;
            }
            break;

        case EGET_FILE_SELECTED:
        {

                                   IGUIFileOpenDialog* dialog =
                                       (IGUIFileOpenDialog*)event.GUIEvent.Caller;
                                   Context.listbox->addItem(dialog->getFileName());
        }
            break;

        case  EGET_LISTBOX_CHANGED:
            switch (id) {
            case CHECK_GUI_ID_INVENTORY_LISTBOX:
                if (((IGUIListBox*)event.GUIEvent.Caller)->getSelected() != -1) {
                    //str=
                    //todo get backend info item
                    //todo sendbackend
                    IGUIElement* par = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_WINDOW, true);
                    IGUIListBox* l = (IGUIListBox*)env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_LISTBOX, true);
                    if (par){
                        rect<s32> pos = par->getAbsolutePosition();
                        if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_ITEM_INFO, true)){
                            env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_INVENTORY_ITEM_INFO, true)->remove();
                        }
                        if (l->getSelected() > -1){
                            showItemInfo((*inventory_items)[l->getSelected()], pos.UpperLeftCorner.X + pos.getWidth(), pos.LowerRightCorner.Y - pos.getHeight(),
                                ITEM_INFO_WINDOW_WIDTH, ITEM_INFO_WINDOW_HEIGHT, env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_SQUAD_WINDOW, true),
                                CHECK_GUI_ID_INVENTORY_ITEM_INFO);
                            //((IGUIListBox*)event.GUIEvent.Caller)->setItem(((IGUIListBox*)event.GUIEvent.Caller)->getSelected(), L"left", 3);
                        }
                    }
                    return true;
                }
                return true;
            case CHECK_GUI_ID_ENDBATTLE_LISTBOXL_WINDOW:{
                                                            IGUIListBox* l = (IGUIListBox*)env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_LISTBOXL_WINDOW, true);
                                                            if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)){
                                                                rect<s32> pos = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)->getAbsolutePosition();
                                                                if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)){
                                                                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)->remove();
                                                                }
                                                                if (l->getSelected() > -1){
                                                                    showItemInfo((*inventory_items)[l->getSelected()], pos.UpperLeftCorner.X + pos.getWidth(), pos.LowerRightCorner.Y - pos.getHeight());
                                                                    //((IGUIListBox*)event.GUIEvent.Caller)->setItem(((IGUIListBox*)event.GUIEvent.Caller)->getSelected(), L"left", 3);
                                                                }
                                                            }
                                                            return true;
            }
            case CHECK_GUI_ID_ENDBATTLE_LISTBOXR_WINDOW:{
                                                            IGUIListBox* l = (IGUIListBox*)env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_LISTBOXR_WINDOW, true);
                                                            if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)){
                                                                rect<s32> pos = env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ENDBATTLE_WINDOW, true)->getAbsolutePosition();
                                                                if (env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)){
                                                                    env->getRootGUIElement()->getElementFromId(CHECK_GUI_ID_ITEMINFO_WINDOW, true)->remove();
                                                                }
                                                                if (l->getSelected() > -1){
                                                                    showItemInfo((*inventory_items)[l->getSelected()], pos.UpperLeftCorner.X + pos.getWidth(), pos.LowerRightCorner.Y - pos.getHeight());
                                                                }
                                                            }

                                                            //((IGUIListBox*)event.GUIEvent.Caller)->setItem(((IGUIListBox*)event.GUIEvent.Caller)->getSelected() , L"right", 3);
                                                            return true;
            }

            }

        default:
            break;
        }
    }

    return false;
}



rect<s32> FieldInterface::getRectPopupWindow(core::position2di pos, s32 width, s32 height) {
    s32 pos_x, pos_y, width_t, height_t;
    if (pos.X + width < SCREEN_WIDTH) {
        pos_x = pos.X + DEFAULT_MARGIN;
    }
    else {
        pos_x = pos.X - DEFAULT_MARGIN - width;
    }
    if (pos.Y - height >0) {
        pos_y = pos.Y - DEFAULT_MARGIN - height;
    }
    else {
        pos_y = pos.Y + DEFAULT_MARGIN;
    }

    height_t = pos_y + height;
    width_t = pos_x + width;

    return rect<s32>(pos_x, pos_y, width_t, height_t);
}

rect<s32> FieldInterface::getRectWindow(s32 x, s32 y, s32 width, s32 height){
        return rect<s32>(x, y, x+width, y +height);
}


void FieldInterface::showUnitInfo( stringw* unit, s32 x, s32 y) {
    //todo get unit info
    //test
    IGUITab* window = env->addTab(
        getRectPopupWindow(position2di(x, y), UNIT_INFO_WINDOW_WIDTH, UNIT_INFO_WINDOW_HEIGHT),
        0, CHECK_GUI_ID_USERINFO_WINDOW);

    env->loadGUI(L"../gametut/media/guiUnitInfo.xml", window);

    IGUIElement* n = *(window->getChildren().begin());
    n->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
    fillGUIFields(n, unit);
}

void FieldInterface::showEquipWindow(std::vector<stringw*>* items, s32 x, s32 y, s32 width, s32 height, IGUIElement* parrent, s32 id) {
    //todo get unit info
    //test                                                     

    IGUITab* window = env->addTab(
        getRectPopupWindow(position2di(x, y), width, height),
        parrent, id == -1 ? CHECK_GUI_ID_EQUIP_WINDOW : id);
    window->setDrawBackground(true);
    env->loadGUI(L"../gametut/media/guiEquip.xml", window);

    list<IGUIElement*>::ConstIterator it = (*(window->getChildren().begin()))->getChildren().begin();
/*

    for (; it != (*(window->getChildren().begin()))->getChildren().end(); it++){
        video::ITexture* image = field->driver->getTexture(L"../gametut/media/Particle.tga");
        ((IGUIButton*)(*it))->setImage(image);
       // ((IGUIButton*)(*it))->setID(GUI_ID_EQUIP_WINDOW_BUTTON);
 
    }*/
    std::vector<stringw*>::iterator ite = items->begin();
    for (int i = 1; i <= 12; i++){
        if ((*(window->getChildren().begin()))->getElementFromId(i)){
            video::ITexture* image = field->driver->getTexture(stringw(PATH_ITEM_PICS) + (*items)[i][FIELDS_INFO_AVATAR]);
            ((IGUIButton*)((*(window->getChildren().begin()))->getElementFromId(i)))->setImage(image);
            ((IGUIButton*)((*(window->getChildren().begin()))->getElementFromId(i)))->setScaleImage(true);
        }
        // ((IGUIButton*)(*it))->setID(GUI_ID_EQUIP_WINDOW_BUTTON);

    }

    IGUIElement* n = *(window->getChildren().begin());
    n->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));

}


void FieldInterface::showItemInfo(stringw* item, s32 x, s32 y, s32 width, s32 height, IGUIElement* parrent, s32 id){
    //todo get unit info
    //test

    IGUITab* window = env->addTab(
        getRectWindow(x, y, width, height),
        parrent, id == -1 ? CHECK_GUI_ID_ITEMINFO_WINDOW: id);

    env->loadGUI(L"../gametut/media/guiItemInfo.xml", window);

    IGUIElement* n = *(window->getChildren().begin());
    n->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
    fillGUIFields(n, item);
}


void FieldInterface::showEndBattleWindow(std::vector<stringw*>* items, std::vector<stringw*>* trophys, s32 x, s32 y){
    IGUITab* window = env->addTab(
        //todo поправить коорды
        getRectPopupWindow(position2di(x, y), END_BATTLE_WINDOW_WIDTH, END_BATTLE_WINDOW_HEIGHT),
        0, CHECK_GUI_ID_ENDBATTLE_WINDOW);
    env->loadGUI(L"../gametut/media/guiEndBattleTrophy.xml", window);
    (*(window->getChildren().begin()))->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
    window->setDrawBackground(true);
    window->setBackgroundColor(SColor(255, 155, 155, 155));

#define GUI_END_BATTLE_LEFT_BUTTON 1
#define GUI_END_BATTLE_RIGHT_BUTTON 2
#define GUI_END_BATTLE_LEFT_TAB_CONTROL 3
#define GUI_END_BATTLE_RIGHT_TAB_CONTROL 4
#define GUI_END_BATTLE_LEFT_TAKE_BUTTON 5

    (*(window->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_LEFT_TAKE_BUTTON)->setID(GUI_ID_END_BATTLE_TAKE_ITEM_BUTTON);
    (*(window->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_LEFT_BUTTON)->setID(GUI_ID_END_BATTLE_TAKE_ALL_BUTTON);
    (*(window->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_RIGHT_BUTTON)->setID(GUI_ID_END_BATTLE_NEXT_BUTTON);

    IGUITabControl* lt = (IGUITabControl*)(*(window->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_LEFT_TAB_CONTROL);
    IGUITabControl* rt = (IGUITabControl*)(*(window->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_RIGHT_TAB_CONTROL);

    //todo get itemlist
    irr::core::stringw str1[10] = { L"all", L"weapon", L"armor", L"other", };


    env->loadGUI(L"../gametut/media/guiTabList.xml", lt);
    env->loadGUI(L"../gametut/media/guiTabList.xml", rt);

    for (int i = 0; i<lt->getTabCount(); i++) {
        IGUIElement* z = lt->getTab(i);
        z->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
        IGUIElement* zq = *(z->getChildren().begin());
        zq->setRelativePositionProportional(rect<f32>(0, 0.10, 1, 0.95));
        zq->setID(CHECK_GUI_ID_ENDBATTLE_LISTBOXL_WINDOW);
        std::vector<stringw*>::iterator it = trophys->begin();
        for (; it != trophys->end(); it++) {
            ((IGUIListBox*)zq)->addItem((*it)[FIELDS_INFO_NAME].c_str());
        }

        z->setText(str1[i].c_str());
        lt->setTabExtraWidth(30);
    }

    for (int i = 0; i<rt->getTabCount(); i++) {
        IGUIElement* z = rt->getTab(i);
        z->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
        IGUIElement* zq = *(z->getChildren().begin());
        zq->setRelativePositionProportional(rect<f32>(0, 0.1, 1, 0.95));
        zq->setID(CHECK_GUI_ID_ENDBATTLE_LISTBOXR_WINDOW);
        std::vector<stringw*>::iterator it = items->begin();
        for (; it != items->end(); it++) {
            ((IGUIListBox*)zq)->addItem((*it)[FIELDS_INFO_NAME].c_str());
        }
        z->setText(str1[i].c_str());
        rt->setTabExtraWidth(30);

        /*env->loadGUI(L"../gametut/media/guiTest.xml", *(lk->getChildren().begin()));
        //IGUIListBox* n = (IGUIListBox*)(*(((*(window->getChildren().begin()))->getChildren().begin())));
        list<IGUIElement*>::ConstIterator l = lk->getChildren().begin();
        ((IGUIListBox*)(*l))->setDrawBackground(true);
        ((IGUIListBox*)(*l))->addItem(L"jjjj");
        ((IGUIListBox*)(*l))->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));*/
    }
    lt->setActiveTab(0);
    rt->setActiveTab(0);

    /*
    list<IGUIElement*>::ConstIterator l = ((*(window1->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_LEFT_TAB_CONTROL))->getChildren().begin();
    for (; l != (*(window1->getChildren().begin()))->getElementFromId(GUI_END_BATTLE_LEFT_TAB_CONTROL)->getChildren().end(); l++) {
    (*l)->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
    }*/

    //window->setBackgroundColor(SColor(0, 150, 155, 155));
    //window->setDrawBackground(true);
    /* IGUITabControl* w = env->addTabControl(
    rect<s32>(pos_x, pos_y, width, height),
    0, CHECK_GUI_ID_USERINFO_WINDOW);
    env->loadGUI(L"../gametut/media/guiTest.xml", w);
    env->loadGUI(L"../gametut/media/guiTest.xml", w);
    w->setTabHeight(10);*/



    //IGUIElement* n = *(window->getChildren().begin());
    //n->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
    //fillGUIFields(n, str);
}

void FieldInterface::fillGUIFields(IGUIElement* n, stringw* str) {

#define NAME "Name"
#define LEVEL "Level"
#define HP "HP"
#define DAMAGE "Damage"
#define DEFENSE "Defense"
#define AVATAR "Avatar"
#define TYPE "Type"
#define REQUIREMENTS "Requirements"
#define BONUSES "Bonuses"
#define COST "Cost"
#define QUALITY "Quality"
#define DESCRIPTION "Description"

    list<IGUIElement*>::ConstIterator l = n->getChildren().begin();

    for (; l != n->getChildren().end(); l++){
        irr::core::stringc wname((*l)->getName());
        if (wname == HP){
            (*l)->setText(str[FIELDS_INFO_HP].c_str());
        }
        else if (wname == LEVEL){
            (*l)->setText(str[FIELDS_INFO_LEVEL].c_str());
        }
        else if (wname == DAMAGE){
            (*l)->setText(str[FIELDS_INFO_DAMAGE].c_str());
        }
        else if (wname == DEFENSE){
            (*l)->setText(str[FIELDS_INFO_DEFENSE].c_str());
        }
        else if (wname == NAME){
            (*l)->setText(str[FIELDS_INFO_NAME].c_str());
        }
        else if (wname == TYPE){
            (*l)->setText(str[FIELDS_INFO_TYPE].c_str());
        }
        else if (wname == REQUIREMENTS){
            (*l)->setText(str[FIELDS_INFO_REQUIREMENTS].c_str());
        }
        else if (wname == BONUSES){
            (*l)->setText(str[FIELDS_INFO_BONUSES].c_str());
        }
        else if (wname == COST){
            (*l)->setText(str[FIELDS_INFO_COST].c_str());
        }
        else if (wname == QUALITY){
            (*l)->setText(str[FIELDS_INFO_QUALITY].c_str());
        }
        else if (wname == DESCRIPTION){
            (*l)->setText(str[FIELDS_INFO_DESCRIPTION].c_str());
        }
        else if (wname == AVATAR){
            video::ITexture* image = field->driver->getTexture(str[FIELDS_INFO_AVATAR].c_str());
            ((IGUIImage*)(*l))->setImage(image);
        }
    }
}


void FieldInterface::showOpenInventory( std::vector<stringw*>* items,s32 x, s32 y, s32 width, s32 height, IGUIElement* parent) {
    IGUITabControl* window = env->addTabControl(
        getRectWindow(x, y, width, height),
        false, // modal?
        L"LIKE INVENTORY", parent, CHECK_GUI_ID_INVENTORY_WINDOW);

    //todo get itemlist
    irr::core::stringw str1[10] = { L"all", L"weapon", L"armor", L"other", };


    env->loadGUI(L"../gametut/media/guiTabList.xml", window);


    for (int i = 0; i < window->getTabCount(); i++) {
        IGUIElement* z = window->getTab(i);
        z->setRelativePositionProportional(rect<f32>(0, 0, 1, 1));
        IGUIElement* zq = *(z->getChildren().begin());
        zq->setRelativePositionProportional(rect<f32>(0, 0.10, 1, 0.95));
        zq->setID(CHECK_GUI_ID_INVENTORY_LISTBOX);
         std::vector<stringw*>::iterator it = items->begin();        
        for (; it != items->end(); it++) {
            ((IGUIListBox*)zq)->addItem((*it)[FIELDS_INFO_NAME].c_str());
        }

        z->setText(str1[i].c_str());
        window->setTabExtraWidth(30);
    }
    window->setActiveTab(0);

}

void FieldInterface::showSquadWindow(std::vector<stringw*>* units) {
    IGUITab* window = env->addTab(
        getRectWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
/*
        false, // modal?
        L"Squad",*/ 0, CHECK_GUI_ID_SQUAD_WINDOW);
    //window->setDraggable(false);

    showOpenInventory(inventory_items,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2,    window);
    rect<s32> pos = window->getAbsolutePosition();
    IGUIButton* b = env->addButton(getRectWindow(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT - DEFAULT_BUTTON_HEIGHT-DEFAULT_MARGIN, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT), window, GUI_ID_INVENTORY_EQUIP_BUTTON, L"equip");
    b = env->addButton(getRectWindow(SCREEN_WIDTH * 3 / 4 + DEFAULT_BUTTON_WIDTH * 2 - DEFAULT_MARGIN, SCREEN_HEIGHT - DEFAULT_BUTTON_HEIGHT - DEFAULT_MARGIN, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT), window, GUI_ID_EQUIP_CLOSE_BUTTON, L"close");

    //showEquipWindow(0, SCREEN_HEIGHT / 2, (SCREEN_HEIGHT / 2)*3/4, SCREEN_HEIGHT / 2, window);

    s32 roww = (SCREEN_WIDTH - 2 * DEFAULT_MARGIN) / 7, rowh = (SCREEN_HEIGHT / 2 - 2 * DEFAULT_MARGIN)/3;

    std::vector<stringw*>::iterator it = units->begin();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            IGUIButton* b = env->addButton(getRectWindow(DEFAULT_MARGIN + roww*(j), DEFAULT_MARGIN + rowh*i, rowh*0.95, rowh*0.95), window, i+j);
            video::ITexture* image = field->driver->getTexture(stringw(PATH_UNIT_FACES) + (*it)[FIELDS_INFO_AVATAR]);
            b->setImage(image);
            b->setScaleImage(true);
            it++;
        }
    }

}


/*
void FieldInterface::showOpenInventory(s32 x, s32 y) {
    IGUIWindow* window = env->addWindow(
        rect<s32>(INVENTORY_WINDOW_POS_X, INVENTORY_WINDOW_POS_Y, INVENTORY_WINDOW_WIDTH, INVENTORY_WINDOW_HEIGHT),
        false, // modal?
        L"LIKE INVENTORY", 0, CHECK_GUI_ID_INVENTORY_WINDOW);
    window->setDrawBackground(true);
    //window->setBackgroundColor (SColor(0, 150, 155, 155));
    s32 win_width = window->getRelativePosition().getWidth();
    s32 win_height = window->getRelativePosition().getHeight();

    IGUIListBox* list = env->addListBox(rect<s32>(DEFAULT_MARGIN, DEFAULT_MARGIN, win_width*0.5, win_height - DEFAULT_MARGIN), window,
        CHECK_GUI_ID_INVENTORY_WINDOW);
    Context.listbox = list;
    for (int i = 0; i < 100; i++) { //test
        list->addItem(L"lol5555555555555555555555555555");
    }
    env->addButton(rect<s32>(win_width - DEFAULT_MARGIN - DEFAULT_BUTTON_WIDTH, win_height - DEFAULT_MARGIN - DEFAULT_BUTTON_HEIGHT, win_width - DEFAULT_MARGIN, win_height - DEFAULT_MARGIN),
        window, GUI_ID_INVENTORY_EQUIP_BUTTON, L"Equip", L"Equip");
    inventoryStaticText =
        env->addStaticText(L"",
        rect<s32>(win_width*0.5 + DEFAULT_MARGIN, DEFAULT_MARGIN, win_width - DEFAULT_MARGIN, win_height*0.5),
        true, // border?
        false, // wordwrap?
        window);
}*/

void FieldInterface::setSelectedSceneNode(scene::ISceneNode* s){
    selectedSceneNode = s;
}


void FieldInterface::testfill(){
    inventory_items = new std::vector<stringw*>;
    inventory_prophy_items = new std::vector<stringw*>;
    squad_units = new std::vector<stringw*>;

    for (int i = 0; i < 22; i++) {
        irr::core::stringw* str = new irr::core::stringw[50];
        str[FIELDS_INFO_AVATAR] = stringw((rand() % 7) + 1) + stringw(L".jpg");
        str[FIELDS_INFO_DAMAGE] = stringw(L"Damage:") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_LEVEL] = stringw(L"Level: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_DEFENSE] = stringw(L"Defense: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_HP] = L"HP: 990/1000";
        str[FIELDS_INFO_NAME] = L"Name: NoOne";
        str[FIELDS_INFO_TYPE] = L"Type: sword";
        str[FIELDS_INFO_REQUIREMENTS] = L"Requirements:\n str: 10\n int: 4";
        str[FIELDS_INFO_BONUSES] = L"Bonuses:\n str: +10\n int: -4";
        str[FIELDS_INFO_COST] = stringw(L"Cost: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_QUALITY] = L"Quality: magic";
        str[FIELDS_INFO_DESCRIPTION] = stringw("The Elder Artefacts, also known as The Elder Twelve, are a class of immensely powerful and divine") +
            stringw("artefacts that were created by the Elder Gods who used them as conduits") +
            stringw("for their power to carefully craft perfect details in their creations.");
        inventory_items->push_back(str);
        *inventory_prophy_items = *inventory_items;
    }

    for (int i = 0; i < 300; i++) {
        irr::core::stringw* str = new irr::core::stringw[50];
        str[FIELDS_INFO_AVATAR] = stringw((rand() % 7) + 1) + stringw(L".jpg");
        str[FIELDS_INFO_DAMAGE] = stringw(L"Damage:") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_LEVEL] = stringw(L"Level: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_DEFENSE] = stringw(L"Defense: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_HP] = L"HP: 990/1000";
        str[FIELDS_INFO_NAME] = L"Name: NoOne";
        str[FIELDS_INFO_TYPE] = L"Type: sword";
        str[FIELDS_INFO_REQUIREMENTS] = L"Requirements:\n str: 10\n int: 4";
        str[FIELDS_INFO_BONUSES] = L"Bonuses:\n str: +10\n int: -4";
        str[FIELDS_INFO_COST] = stringw(L"Cost: ") + stringw((rand() % 50) + 1);
        str[FIELDS_INFO_QUALITY] = L"Quality: magic";
        str[FIELDS_INFO_DESCRIPTION] = stringw("The Elder Artefacts, also known as The Elder Twelve, are a class of immensely powerful and divine") +
            stringw("artefacts that were created by the Elder Gods who used them as conduits") +
            stringw("for their power to carefully craft perfect details in their creations.");


        squad_units->push_back(str);
    }


}