#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player {
  public:
    Warrior(const Zeni::Point2f &position_,
            const int &uid_,
            const Team &team_,
            const Zeni::Vector2f &size_ = OBJECT_SIZE);

    void render() const override;
  
    Weapon* melee() override;

    Weapon* melee(const float &direction) override;
  
    Weapon* warrior_spc_skill() override;

    Zeni::String get_skill_str() const override {return "warrior_skill"; }
};

#endif /* WARRIOR_H */
