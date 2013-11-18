#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player
{
  Warrior(const Zeni::Point2f &position_);
  ~Warrior();

  void render();

  Weapon* melee();
  void spc_attack();
};


#endif /* WARRIOR_H */