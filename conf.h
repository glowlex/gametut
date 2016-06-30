
#ifndef CONF_H
#define CONF_H
#pragma once

#include <Keycodes.h>

extern  int g_screen_width;
extern  int g_screen_height;
extern  bool g_start_game;
extern  bool g_quit_game;

#define SCREEN_WIDTH   g_screen_width
#define SCREEN_HEIGHT  g_screen_height

#define PATH_UNIT_FACES L"../gametut/pics/faces_3d/"
#define PATH_ITEM_PICS L"../gametut/pics/equipment/"
#define PATH_UNIT_MODEL L"../gametut/pics/military/"

#define MOVEMENT_SPEED  500.f;

#define FILDSIZE 40
#define CELLSIZE 256
#define INVENTORY_WINDOW_POS_X g_screen_width*0.2
#define INVENTORY_WINDOW_POS_Y g_screen_height*0.2
#define INVENTORY_WINDOW_WIDTH g_screen_width*0.4
#define INVENTORY_WINDOW_HEIGHT g_screen_height*0.6

#define UNIT_INFO_WINDOW_WIDTH g_screen_width*0.20
#define UNIT_INFO_WINDOW_HEIGHT g_screen_height*0.2

#define ITEM_INFO_WINDOW_WIDTH g_screen_width*0.25
#define ITEM_INFO_WINDOW_HEIGHT g_screen_height*0.3

#define EQUIP_INFO_WINDOW_WIDTH  g_screen_height*3/8
#define EQUIP_INFO_WINDOW_HEIGHT g_screen_height*1/2

#define END_BATTLE_WINDOW_WIDTH g_screen_width*0.6
#define END_BATTLE_WINDOW_HEIGHT g_screen_height*0.6
#define END_BATTLE_WINDOW_POS_X (SCREEN_WIDTH-END_BATTLE_WINDOW_WIDTH-ITEM_INFO_WINDOW_WIDTH)/2
#define END_BATTLE_WINDOW_POS_Y (SCREEN_HEIGHT-END_BATTLE_WINDOW_HEIGHT)/2


#define DEFAULT_MARGIN 20
#define DEFAULT_BUTTON_WIDTH 110
#define DEFAULT_BUTTON_HEIGHT 32

enum fieldInfoEnum
{
    FIELDS_INFO_NAME = 1,
    FIELDS_INFO_LEVEL,
    FIELDS_INFO_HP,
    FIELDS_INFO_DAMAGE,
    FIELDS_INFO_DEFENSE,
    FIELDS_INFO_AVATAR,
    FIELDS_INFO_TYPE,
    FIELDS_INFO_REQUIREMENTS,
    FIELDS_INFO_BONUSES,
    FIELDS_INFO_COST,
    FIELDS_INFO_QUALITY,
    FIELDS_INFO_DESCRIPTION,
    FIELDS_INFO_ID
};


enum 
{
    CHECK_GUI_ID_INVENTORY_WINDOW = 2001,
    CHECK_GUI_ID_USERINFO_WINDOW,
    CHECK_GUI_ID_ENDBATTLE_WINDOW,
    CHECK_GUI_ID_ENDBATTLE_LISTBOXL_WINDOW,
    CHECK_GUI_ID_ENDBATTLE_LISTBOXR_WINDOW,
    CHECK_GUI_ID_ITEMINFO_WINDOW,
    CHECK_GUI_ID_EQUIP_WINDOW,
    CHECK_GUI_ID_SQUAD_WINDOW,
    CHECK_GUI_ID_INVENTORY_LISTBOX,
    CHECK_GUI_ID_INVENTORY_ITEM_INFO,
    CHECK_GUI_ID_EQUIP_ITEM_INFO,

};


// Определим несколько уникальных идентификаторов для наших gui элементов.
enum
{
    GUI_ID_QUIT_BUTTON = 1001, // id кнопки выхода из приложения
    GUI_ID_NEW_WINDOW_BUTTON, // id кнопки создания нового окна
    GUI_ID_FILE_OPEN_BUTTON, // id кнопки открытия диалога для выбора файлов
    GUI_ID_TRANSPARENCY_SCROLL_BAR, // id полосы прокрутки
    GUI_ID_ENDTURN_BUTTON,
    GUI_ID_SELECTED_ITEM,
    GUI_ID_OPEN_INVENTORY,
    GUI_ID_INVENTORY_EQUIP_BUTTON,
    GUI_ID_START_GAME_BUTTON,
    GUI_ID_LOAD_GAME_BUTTON,
    GUI_ID_END_BATTLE_TAKE_ALL_BUTTON,
    GUI_ID_END_BATTLE_NEXT_BUTTON,
    GUI_ID_END_BATTLE_TAKE_ITEM_BUTTON,
    GUI_ID_EQUIP_BUTTON,
    GUI_ID_SQUAD_BUTTON,
    GUI_ID_EQUIP_CLOSE_BUTTON,
    GUI_ID_EQUIP_WINDOW_BUTTON,
    GUI_ID_EQUIP_PICK_WINDOW_BUTTON,
};

enum
{
    BUTTON_ID_SKIP_UNIT_MOVE = irr::KEY_SPACE,
    BUTTON_ID_END_TAKE_ITEM_BUTTON = irr::KEY_SPACE,
};

enum equipWindow
{
    WEAPON1 =1,
    HEAD,
    IMPLANT1,
    WEAPON2,
    BODY,
    IMPLANT2,
    EMP,
    LEGS,
    IMPLANT3,
    GLOVES,
    BOOTS,
    IMPLANT4
};

#endif