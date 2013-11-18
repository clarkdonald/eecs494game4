#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"

class Archer : public Player
{
  public:
    Archer(const Zeni::Point2f &position_);
    ~Archer();

  void render() const override;

  Weapon* range() override;
  void spc_skill() override;
};


#endif /* ARCHER_H */