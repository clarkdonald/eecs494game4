#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player {
  public:
    Warrior(const Zeni::Point2f &position_,
            const int &uid_,
            const Team &team_);

    void render() const override;
  
    Weapon* melee() override;

    Weapon* melee(const float &direction) override;
  
    void warrior_spc_skill(bool pressed) override;

    Zeni::String get_skill_str() const override {return "warrior_skill"; }
};

#endif /* WARRIOR_H */
