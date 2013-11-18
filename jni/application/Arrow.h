#ifndef ARROW_H
#define ARROW_H

#include "Weapon.h"

class Arrow : public Weapon
{
  public:
    Arrow(const Zeni::Point2f &position_);
    ~Arrow();

    void render();

  private:

};


#endif /* ARROW_H */