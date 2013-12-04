#ifndef SHIELD_H
#define SHIELD_H

#include "Weapon.h"
#include "Player.h"

#define SKILL_DURATION 5.0f

class Shield : public Weapon {
  public:
    Shield(const Zeni::Point2f&, const float&, const Team &, Player*);

    void render() const override;
    bool animation_over() override;

    void remove_from_owner() override;
  private:
    Player* owner;
    float dir;
};

#endif /* SHIELD_H */
