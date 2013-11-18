#ifndef ARROW_H
#define ARROW_H

#include "Weapon.h"

#define ARROW_SPD 50.0f

class Arrow : public Weapon
{
  public:
    Arrow(const Zeni::Point2f&, const float&);
    ~Arrow();

    void render() const override;
    void update(const float);
  private:
    Zeni::Vector2f move_vec;
};


#endif /* ARROW_H */