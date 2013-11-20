#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
  public:
    Sword(const Zeni::Point2f&, const float&, const Team &);

    void render() const override;
  
  private:
    float dir;
};

#endif /* SWORD_H */
