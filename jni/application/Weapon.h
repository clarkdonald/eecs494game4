#ifndef WEAPON_H
#define WEAPON_H

#include "Game_Object.h"

class Weapon : public Game_Object
{
  public:
	  Weapon(const Zeni::Point2f &position_);
    virtual ~Weapon() {};

	  virtual void render() = 0;

  protected:
	  float damage;
};

#endif /* WEAPON_H */