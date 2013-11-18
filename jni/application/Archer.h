#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"

class Archer : public Player
{
  public:
    Archer(const Zeni::Point2f &position_);
    ~Archer();

    void render();

    Weapon* range();
    void spc_attack();
};


#endif /* ARCHER_H */