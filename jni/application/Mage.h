#ifndef MAGE_H
#define MAGE_H

#include "Player.h"

class Mage : public Player
{
  public:
    Mage(const Zeni::Point2f &position_);
    ~Mage();

    void render();

    Weapon* range();
    void spc_attack();
};


#endif /* MAGE_H */