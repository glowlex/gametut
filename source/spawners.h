#pragma once

#include <ctime>
#include <cmath>
#include <cstdlib>

#include "gtl_rpg.h"
#include "database.h"

namespace spawners {

  using namespace gtl_rpg;

  //NPC behavior template stat modifiers

  const int BASE_NONDEF_PROB = 40;               //base chance to spawn a common mob
  const int BASE_TANK_PROB = 20;                 //base chance to spawn a "tank" mob
  const int BASE_SUPPORT_PROB = 20;              //base chance to spawn a healer/supporter mob
  const int BASE_DAMAGER_PROB = 20;              //base chance to spawn a damager mob

  const int BASE_LEADER_PROB = 10;               //chance to spawn a pack leader leader
  const int BASE_MASS_LEADER_PROB = 20;          //chance to spawn a mass-leader

  const double NONDEF_HP_MODIFIER = 1.0;
  const double NONDEF_DMG_MODIFIER = 1.0;
  const double NONDEF_DEF_MODIFIER = 1.0;

  const double GRUNT_HP_MODIFIER = 1.50;
  const double GRUNT_DMG_MODIFIER = 0.50;
  const double GRUNT_DEF_MODIFIER = 2.25;

  const double SUPPORT_HP_MODIFIER = 0.75;
  const double SUPPORT_DMG_MODIFIER = 1.25;
  const double SUPPORT_DEF_MODIFIER = 0.50;

  const double DAMAGER_HP_MODIFIER = 0.50;
  const double DAMAGER_DMG_MODIFIER = 2.25;
  const double DAMAGER_DEF_MODIFIER = 0.75;
 
  const double LEADER_HP_MODIFIER = 1.50;
  const double LEADER_DMG_MODIFIER = 1.50;
  const double LEADER_DEF_MODIFIER = 1.50;
  const double LEADER_EXP_MODIFIER = 1.50;
  const double LEADER_CASH_MODIFIER = 1.50;

  const double MASS_LEADER_HP_MODIFIER = 1.25;
  const double MASS_LEADER_DMG_MODIFIER = 1.25;
  const double MASS_LEADER_DEF_MODIFIER = 1.25;
  const double MASS_LEADER_EXP_MODIFIER = 1.25;
  const double MASS_LEADER_CASH_MODIFIER = 1.25;

  //=======================================================================================\\
  //--------------------��������� �������� ��������� (��������� ��������)------------------\\
  //������ ��������� ������������ ��� ��������� �������� �������� �� ������� �� ���� ������\\
  //--��� ������ ������������� �������� ������������ ����������� ���������� �������������--\\
  //---��������, ��������� �� ������� ��� �������� (��������). ��������� TRASH < 1, �.�.---\\
  //----������� ���� ������ ������������� �������� IR_COMMON = 1.0, � IR_TRASH ����, ���---\\
  //----------------------------------------IR_COMMON.-------------------------------------\\
  /*=======================================================================================*/

  const double TRASH_MODIFIER = 0.75;    //����������� "�����" ��������� (�����)
  const double COMMON_MODIFIER = 1.0;    //���������� "�����" ��������� (�������)
  const double GOOD_MODIFIER = 1.25;     //����������� "�������" ��������� (������������)
  const double RARE_MODIFIER = 1.5;      //����������� "�����" ��������� (������)
  const double EPIC_MODIFIER = 1.75;     //����������� "����������" ��������� (���������)
  const double LEGENDARY_MODIFIER = 2.0; //����������� "���������" ��������� (�����������)
  const double QUALITY_MODIFIER = 0.25;  //���������� ����������� ��������

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //---------------------------!������������ ������ ��������!------------------------------\\
  //----------��������� ��������� ����� ������� �������������� ��� ��������� � ���---------\\
  //----------� ����������� ������ ��������. ������, �������� ��������� ���������----------\\
  //--------������������� ������ �� � ���� ��������� � ����-��������� ��� ����������-------\\
  //--------���������. ����� ��������� ��������� ������ ���������� ��������� �������-------\\
  //--------� ������� ����� ���������� � ����������� ���������. ������������ ��������------\\
  //------------------����������� ����� ������������� ������������� ������.----------------\\
  //=======================================================================================\\	

  const double STAT_MODIFER = 0.14;    //����������� ����������/������� � �������������� ��������
  const double COST_MODIFIER = 0.03;   //����������� ���� ��������
  const double DAMDEF_MODIFIER = 0.18; //����������� ����� � ���������� ������

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //---------------------------!������������ ��������� ������!-----------------------------\\
  //------------------����������� ��� ���������� ��������� ������ �� � �����---------------\\
  //=======================================================================================\\
	
  const double EXP_CAP_RAISE = 0.25; //��������� ���� �� ������ ������
  const double MOB_DMG_RAISE = 0.08; //��������� �����, ���������� �����
  const double HP_CAP_RAISE = 0.10;  //��������� ���� ��
  const double MOB_DEF_RAISE = 0.09; //��������� ������ ����
  const double CASH_RAISE = 0.10;    //��������� �������� �������
  const double EXP_RAISE = 0.10;     //��������� ������� � �����

  //=======================================================================================\\
  /*=======================================================================================*/

  struct TItemIgData //��������� ������������� ���������� ��������
  {
    int name;                      //�������� �������� (������ � ���� ������)
    int description;			   //�������� ��������
    int manufacturer;              //������ �����-������������� � ���� ������
    int cost;                      //��������� ��������
    int lvlreq;                    //���������� � ������ �������� ��� �������������
    int statreq[database::STATS_COUNT];      //���������� � ��������������� �������� ��� �������������
    int statbons[database::STATS_COUNT];     //����� � ��������������� �������� ��� ������������
    int hpbons;                    //����������� �� ��� �������������
    int ntbons;                    //����������� ������� ��� �������������
    bool slots[ES_SIZE];           //�����, ���� ����� ����������� �������
    int dist;                      //��������� ����� (��� ����� � ��������� ������ ������� FREE_INDEX)
    int dmg[PAIR_ARR_SIZE];        //�������� ���� (������������/�����������)
    int def;                       //�����
    int stack;                     //����� ��������� � ������
    bool usable;                   //�������� �� ������� ������������
    bool disposable;               //�������� �� �����������
    bool ifstack;                  //����� �� ���������� � ������
    int durability[PAIR_ARR_SIZE]; //����� ��������� (������������/�������)
    gtl_rpg::TEquipmentKind kind;           //��� ��������
    gtl_rpg::TItemRareness rarity;          //������� �������� ��������
  };

  struct TMobIgData //mob data (in-game generated for battle)
  {
    int faction;
    int dmg[PAIR_ARR_SIZE];
    int hp[PAIR_ARR_SIZE];
    int def;
    int level;
    int loot;
    int ini;
    database::TNPCRole role;
    bool is_leader;
    bool is_mass_leader;
  };

  void copy_item(struct TItemIgData *from, struct TItemIgData *to);
  void swap_item(struct TItemIgData *from, struct TItemIgData *to);
  void clear_item(struct TItemIgData *item);
  void copy_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  void swap_mob_data(struct TMobIgData *from, struct TMobIgData *to);
  void clear_mob_data(struct TMobIgData *data);

  class Mob  //in-game mobs spawner class
  {
    public:

      static spawners::TMobIgData spawn(TMobIgData *inp_data);
      static spawners::TMobIgData spawn(database::TMobStData *inp_data);
      static spawners::TMobIgData spawn(database::TMobStData *inp_data, int low_level_cap, int high_level_cap);
      static void Check_Leadership(TMobIgData *mob_data, bool already_have_a_leader, bool already_have_a_mass_leader);

  };

  class Item //in-game items spawner class
  {
  public:

	  static spawners::TItemIgData spawn(struct database::TItemStData *data);
	  static spawners::TItemIgData spawn(struct database::TItemStData *data, int llc, int hlc);

  };
}
