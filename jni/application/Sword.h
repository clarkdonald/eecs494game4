#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"
#include "Player.h"

#define SWING_TIME 0.15f

class Sword : public Weapon {
  public:
    Sword(const Zeni::Point2f&, const float&, const Team &, Player*);

    void render() const override;
    bool animation_over() override;

  private:
    Player* owner;
    float dir;
};

#endif /* SWORD_H */
