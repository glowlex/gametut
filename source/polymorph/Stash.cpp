#include "Stash.h"

int Stash::extract_cash(int &where_to) {
  where_to += _cash;
  _cash = 0;
  return 0;
}

int Stash::extract_exp(int &where_to) {
  where_to += _exp;
  _exp = 0;
  return 0;
}

int Stash::add_cash(int &value) {
  _cash += value;
  return 0;
}

int Stash::add_exp(int &value) {
  _exp += value;
  return 0;
}
