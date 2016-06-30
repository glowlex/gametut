#pragma once
#include "gtl_rpg.h"
#include "player.h"


namespace database
{
  using namespace gtl_rpg;

  const int STATS_COUNT = 8;

  enum TNPCRole { NR_NONDEF, NR_GRUNT, NR_DMG, NR_SUPPORT, NR_SIZE }; //тип моделей поведения НИП в бою
  //nr_nondef-стандартный моб, nr_grunt-громила, nr_dmg-дамагер, nr_support-поддержка
    
  struct TLoot //структура данных элемента лут-листа
  {
    int max_quant; //максимально возможное количество данных предметов, которое может выпасть
    int poss;      //вероятность выпадения предмета
    int id;        //идентификатор шаблона предмета в базе данных
  };

  struct TLootList //структура лут-листа (можно применять к мобам или наградам за квесты)
  {
    TLoot loot[LOOT_LIST_SIZE]; //список предметов, которые могут выпасть
    int cash;                   //денежная награда (число, вокруг которог строится разброс)
    int exp;                    //награда в очках опыта
  };

  struct TItemStData //структура шаблонных параметров предмета (хранится в базе данных, на ее основе генерируются игровые предметы)
  {
    int name;                  //название предмета (индекс в базе данных)
    int description;		   //описание предмета
    int imgname;			   //имя файла картинки предмета
    int manufacturer;          //индекс фирмы производителя в базе данных
    int dist;                  //дистанция атаки (для брони и холодного оружия ставить FREE_INDEX)
    int drop_rates[IR_SIZE];   //шансы получить предмет определенного уровня качества из добычи
    //требования предмета
    int lvlreq;                //требования к уровню носителя, чтобы экипировать предмет
    int statreq[STATS_COUNT];  //требования к характеристикам носителя, чтобы экипировать предмет
    int dmg[PAIR_ARR_SIZE];    //наносимы урон (максимальный/минимальный)
    int def;                   //броня
    int quest;                 //идентификатор связанного с предметом квеста
    int cost;                  //стоимость предмета
    int durability;            //максимальный запас прочности
    int hpbons;                //исцеление при использовании
    int ntbons;                //восполнение сытости при использовании
    int statbons[STATS_COUNT]; //бонусы к характеристикам персонажа
    bool usable;               //является ли предмет используемым
    bool disposable;           //является ли расходником
    bool ifstack;              //можно ли складывать в стопку
    bool slots[ES_SIZE];       //слоты, в котороые можно экипировать предмет
    TEquipmentKind kind;       //вид предмета
  };

  struct TMobStData //структура данных шаблона типа мобов (используется для генерации пака и хранится в базе данных)
  {
    int faction;            //фракция, которой принадлежит данный тип мобов
    int hp;                 //ХП шаблонного моба первого уровня
    int dmg[PAIR_ARR_SIZE]; //базовый урон моба первого уровня
    int def;                //базовая защита шаблонного моба первого уровня
    bool roles[NR_SIZE];    //достsупные роли для данного типа мобов
    int loot;               //шаблонный лут-лист данного типа мобов
    int dp;					//константа уменьшения вероятности спавна нового моба
    int ini;				//инициатива моба
  };

  struct TLocationStData
  {
    int combat_probs[MAX_PACKS_COUNT][PAIR_ARR_SIZE]; //массив вероятностей спавна паков мобов определенного типа. Каждой локации можно приписать до MAX_PACKS_COUNT разных типов мобов, первое число - индекс пака в базе данных, второе - вероятность спавна пака
    int trader_probs[TK_SIZE];                        //вероятности спавна разных типов торговцев в данной локации	
    TLocationKind kind;                               //
  };

  struct TAbilityData //структура данных способности
  {
    std::string name;					  //название способности
    std::string description;			  //описание способности
    int tgt_number;						  //максимальное число целей
    int area;							  //радиус действия (для не аое/хое ставить FREE_INDEX)
    int range;							  //дальность действия (для шаблона атаки оружием оставить FREE_INDEX)
    int duration;						  //время действия (для всего, кроме дотов/хотов, ставить FREE_INDEX)
    int effect[TS_SIZE][PAIR_ARR_SIZE];	  //матрица эффектов способности (мин. и макс. пределы без учета крита, на которые способность изменяет параметр)
    int tick[TS_SIZE][PAIR_ARR_SIZE];	  //матрица эффектов одного тика (для всего, кроме дотов/хотов, ставить FREE_INDEX)
    bool application[AT_SIZE];			  //возможность применимости способностей
    TPairAffectance affect_kind[TS_SIZE]; //вид воздействия на парные параметры (на сольные воздействуемые параметры ставить PA_BOTH, если параметр не используется, ставить PA_NONDEF)
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
