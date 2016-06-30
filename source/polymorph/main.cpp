#include "Forge.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <locale.h>
#include <windows.h>

int main() {
 // setlocale(LC_ALL,"UTF-8");
  srand(static_cast<unsigned int>(time(0)));
  unsigned int rnd = rand() % 10 + 5;
  std::string db_name;
  db_name = "classic2.db";
  Forge* forge = new Forge("classic2.db");
  for (size_t i = 0; i < rnd; ++i) {
  	Item* created = NULL;
  	int item_lvl = rand() % MAX_LEVEL + START_LEVEL;
  	int key = rand() % EK_LIGHT + 1;
    int code = forge->MakeItem(key, item_lvl , &created);
    std::string response;
    code = created->what(response);
    printf(response.data());
    delete created;
    Sleep(1000);
  }
  delete forge;
  system("pause");
  return 0;
}
