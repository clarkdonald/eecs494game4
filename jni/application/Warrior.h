#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player
{
  public:
    Warrior(const Zeni::Point2f &position_, const int &uid_);
    ~Warrior();

    void render() const override;

    Weapon* melee(const float) override;
    void spc_skill() override;
};


#endif /* WARRIOR_H */