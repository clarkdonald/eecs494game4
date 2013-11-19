#ifndef MAGIC_H
#define MAGIC_H

#include "Weapon.h"

#define MAGIC_SPD 20.0f

class Magic : public Weapon
{
  public:
    Magic(const Zeni::Point2f&, const float&);
    ~Magic();

    void render() const override;
    void update(const float) override;

  private:
    Zeni::Vector2f move_vec;
};

#endif /* MAGIC_H */