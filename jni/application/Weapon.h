#ifndef WEAPON_H
#define WEAPON_H

#include "Game_Object.h"

class Weapon : public Game_Object
{
  public:
	  Weapon(const Zeni::Point2f &position_);
    virtual ~Weapon() {}

    virtual void update(float) {};
	  virtual void render() const = 0;

  protected:
	  float damage;
};

#endif /* WEAPON_H */