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
  //--------------------КОНСТАНТЫ КАЧЕСТВА ПРЕДМЕТОВ (КОНСТАНТЫ РЕДКОСТИ)------------------\\
  //данные константы предназнчены для генерации игрового предмета по шаблону из базы данных\\
  //--При помощи нижеследующих констант производится модификация параметров генерируемого--\\
  //---предмета, зависящих от степени его редкости (качества). Константа TRASH < 1, т.к.---\\
  //----шаблоны базы данных соответствуют редкости IR_COMMON = 1.0, а IR_TRASH хуже, чем---\\
  //----------------------------------------IR_COMMON.-------------------------------------\\
  /*=======================================================================================*/

  const double TRASH_MODIFIER = 0.75;    //модификатор "серых" предметов (хлама)
  const double COMMON_MODIFIER = 1.0;    //модфикатор "белых" предметов (обычных)
  const double GOOD_MODIFIER = 1.25;     //модификатор "зеленых" предметов (качественных)
  const double RARE_MODIFIER = 1.5;      //модификатор "синих" предметов (редких)
  const double EPIC_MODIFIER = 1.75;     //модификатор "фиолетовых" предметов (эпических)
  const double LEGENDARY_MODIFIER = 2.0; //модификатор "оранжевых" предметов (легендарных)
  const double QUALITY_MODIFIER = 0.25;  //аддитивный модификатор качества

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //---------------------------!МОДИФИКАТОРЫ УРОВНЯ ПРЕДМЕТА!------------------------------\\
  //----------прототипы предметов имеют базовые характеристики для заданного у них---------\\
  //----------в требованиях уровня предмета. Однако, возможна генерация предметов----------\\
  //--------произвольного уровня на Х выше заданного в дата-хранилище для выбранного-------\\
  //--------прототипа. Тогда параметры прототипа должны изменяться сообразно разнице-------\\
  //--------в уровнях между прототипом и создаваемым предметом. Модификаторы редкости------\\
  //------------------применяются после использования модификаторов уровня.----------------\\
  //=======================================================================================\\	

  const double STAT_MODIFER = 0.14;    //модификатор требований/бонусов к харктеристикам носителя
  const double COST_MODIFIER = 0.03;   //модификатор цены предмета
  const double DAMDEF_MODIFIER = 0.18; //модификатор урона и показателя защиты

  //=======================================================================================\\
  //=======================================================================================\\

  //=======================================================================================\\
  //---------------------------!МОДИФИКАТОРЫ ПОВЫШЕНИЯ УРОВНЯ!-----------------------------\\
  //------------------применяются при процедурах повышения уровня ИП и мобов---------------\\
  //=======================================================================================\\
	
  const double EXP_CAP_RAISE = 0.25; //повышение капа до нового уровня
  const double MOB_DMG_RAISE = 0.08; //повышение урона, наносимого мобом
  const double HP_CAP_RAISE = 0.10;  //повышение капа ХП
  const double MOB_DEF_RAISE = 0.09; //повышение защиты моба
  const double CASH_RAISE = 0.10;    //повышение денежной награды
  const double EXP_RAISE = 0.10;     //повышение награды в опыте

  //=======================================================================================\\
  /*=======================================================================================*/

  struct TItemIgData //структура внутриигровых параметров предмета
  {
    int name;                      //название предмета (индекс в базе данных)
    int description;			   //описание предмета
    int manufacturer;              //индекс фирмы-производителя в базе данных
    int cost;                      //стоимость предмета
    int lvlreq;                    //требования к уровню носителя для использования
    int statreq[database::STATS_COUNT];      //требования к характеристикам носителя для использования
    int statbons[database::STATS_COUNT];     //бонус к характеристикам носителя при экипировании
    int hpbons;                    //восполнение ХП при использовании
    int ntbons;                    //восполнение сытости при использовании
    bool slots[ES_SIZE];           //слоты, куда можно экипировать предмет
    int dist;                      //дистанция атаки (для брони и холодного оружия ставить FREE_INDEX)
    int dmg[PAIR_ARR_SIZE];        //наносимы урон (максимальный/минимальный)
    int def;                       //броня
    int stack;                     //число предметов в стопке
    bool usable;                   //является ли предмет используемым
    bool disposable;               //является ли расходником
    bool ifstack;                  //можно ли складывать в стопку
    int durability[PAIR_ARR_SIZE]; //запас прочности (максимальный/текущий)
    gtl_rpg::TEquipmentKind kind;           //вид предмета
    gtl_rpg::TItemRareness rarity;          //уровень качества предмета
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
