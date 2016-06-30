#pragma once
#include "gtl_rpg.h"
#include "player.h"


namespace database
{
  using namespace gtl_rpg;

  const int STATS_COUNT = 8;

  enum TNPCRole { NR_NONDEF, NR_GRUNT, NR_DMG, NR_SUPPORT, NR_SIZE }; //��� ������� ��������� ��� � ���
  //nr_nondef-����������� ���, nr_grunt-�������, nr_dmg-�������, nr_support-���������
    
  struct TLoot //��������� ������ �������� ���-�����
  {
    int max_quant; //����������� ��������� ���������� ������ ���������, ������� ����� �������
    int poss;      //����������� ��������� ��������
    int id;        //������������� ������� �������� � ���� ������
  };

  struct TLootList //��������� ���-����� (����� ��������� � ����� ��� �������� �� ������)
  {
    TLoot loot[LOOT_LIST_SIZE]; //������ ���������, ������� ����� �������
    int cash;                   //�������� ������� (�����, ������ ������� �������� �������)
    int exp;                    //������� � ����� �����
  };

  struct TItemStData //��������� ��������� ���������� �������� (�������� � ���� ������, �� �� ������ ������������ ������� ��������)
  {
    int name;                  //�������� �������� (������ � ���� ������)
    int description;		   //�������� ��������
    int imgname;			   //��� ����� �������� ��������
    int manufacturer;          //������ ����� ������������� � ���� ������
    int dist;                  //��������� ����� (��� ����� � ��������� ������ ������� FREE_INDEX)
    int drop_rates[IR_SIZE];   //����� �������� ������� ������������� ������ �������� �� ������
    //���������� ��������
    int lvlreq;                //���������� � ������ ��������, ����� ����������� �������
    int statreq[STATS_COUNT];  //���������� � ��������������� ��������, ����� ����������� �������
    int dmg[PAIR_ARR_SIZE];    //�������� ���� (������������/�����������)
    int def;                   //�����
    int quest;                 //������������� ���������� � ��������� ������
    int cost;                  //��������� ��������
    int durability;            //������������ ����� ���������
    int hpbons;                //��������� ��� �������������
    int ntbons;                //����������� ������� ��� �������������
    int statbons[STATS_COUNT]; //������ � ��������������� ���������
    bool usable;               //�������� �� ������� ������������
    bool disposable;           //�������� �� �����������
    bool ifstack;              //����� �� ���������� � ������
    bool slots[ES_SIZE];       //�����, � �������� ����� ����������� �������
    TEquipmentKind kind;       //��� ��������
  };

  struct TMobStData //��������� ������ ������� ���� ����� (������������ ��� ��������� ���� � �������� � ���� ������)
  {
    int faction;            //�������, ������� ����������� ������ ��� �����
    int hp;                 //�� ���������� ���� ������� ������
    int dmg[PAIR_ARR_SIZE]; //������� ���� ���� ������� ������
    int def;                //������� ������ ���������� ���� ������� ������
    bool roles[NR_SIZE];    //����s����� ���� ��� ������� ���� �����
    int loot;               //��������� ���-���� ������� ���� �����
    int dp;					//��������� ���������� ����������� ������ ������ ����
    int ini;				//���������� ����
  };

  struct TLocationStData
  {
    int combat_probs[MAX_PACKS_COUNT][PAIR_ARR_SIZE]; //������ ������������ ������ ����� ����� ������������� ����. ������ ������� ����� ��������� �� MAX_PACKS_COUNT ������ ����� �����, ������ ����� - ������ ���� � ���� ������, ������ - ����������� ������ ����
    int trader_probs[TK_SIZE];                        //����������� ������ ������ ����� ��������� � ������ �������	
    TLocationKind kind;                               //
  };

  struct TAbilityData //��������� ������ �����������
  {
    std::string name;					  //�������� �����������
    std::string description;			  //�������� �����������
    int tgt_number;						  //������������ ����� �����
    int area;							  //������ �������� (��� �� ���/��� ������� FREE_INDEX)
    int range;							  //��������� �������� (��� ������� ����� ������� �������� FREE_INDEX)
    int duration;						  //����� �������� (��� �����, ����� �����/�����, ������� FREE_INDEX)
    int effect[TS_SIZE][PAIR_ARR_SIZE];	  //������� �������� ����������� (���. � ����. ������� ��� ����� �����, �� ������� ����������� �������� ��������)
    int tick[TS_SIZE][PAIR_ARR_SIZE];	  //������� �������� ������ ���� (��� �����, ����� �����/�����, ������� FREE_INDEX)
    bool application[AT_SIZE];			  //����������� ������������ ������������
    TPairAffectance affect_kind[TS_SIZE]; //��� ����������� �� ������ ��������� (�� ������� �������������� ��������� ������� PA_BOTH, ���� �������� �� ������������, ������� PA_NONDEF)
  };
	
  void copy_loot(struct TLoot *from, struct TLoot *to);
  void swap_loot(struct TLoot *from, struct TLoot *to);
  void clear_loot(struct TLoot *data);
  void copy_loot_list(struct TLootList *from, struct TLootList *to);
  void swap_loot_list(struct TLootList *from, struct TLootList *to);
  void clear_loot_list(struct TLootList *data);
  void copy_item(struct TItemStData *from, struct TItemStData *to);
  void swap_item(struct TItemStData *from,struct TItemStData *to);
  void clear_item(struct TItemStData *item);
  void copy_mob_data(struct TMobStData *from, struct TMobStData *to);
  void swap_mob_data(struct TMobStData *from, struct TMobStData *to);
  void clear_mob_data(struct TMobStData *data);
  void copy_location_data(struct TLocationStData *from, struct TLocationStData *to);
  void swap_location_data(struct TLocationStData *from, struct TLocationStData *to);
  void clear_location_data(struct TLocationStData *data);
  void copy_ability_data(struct TAbilityData *from, struct TAbilityData *to);
  void swap_ability_data(struct TAbilityData *from, struct TAbilityData *to);
  void clear_ability_data(struct TAbilityData *data);
  
  class Database
  {
    public:
      Database();
      ~Database();

      database::TItemStData get_item(int ind);
      database::TMobStData get_mob(int ind);
      database::TLootList get_loot_list(int ind);
      int get_items_size();
      int get_mobs_size();
      int get_loot_list_size();
      bool set_item(struct TItemStData *data);
      bool set_mob(struct TMobStData *data);
      bool set_loot_list(struct TLootList *data);
      bool remove_item(int ind);
      bool remove_mob(int ind);
      bool remove_loot_list(int ind);

    private:
      std::vector<TItemStData> items;
      std::vector<TMobStData> mobs;
      std::vector<TLootList> loot;

  };
}
