#ifndef MAGE_H
#define MAGE_H

#include "Player.h"

class Mage : public Player {
  public:
    Mage(const Zeni::Point2f &position_,
         const int &uid_,
         const Team &team_);

    void render() const override;

    Weapon* range() override;
  
    void spc_skill() override;
};

#endif /* MAGE_H */