#ifndef WEAPON_H
#define WEAPON_H

#include "Game_Object.h"

class Weapon : public Game_Object {
  public:
	  Weapon(const Zeni::Point2f &position_, const float &damage_);
  
    virtual ~Weapon() = 0;

    virtual void update(const float) {}
  
	  virtual void render() const = 0;

    const float & get_damage() const {return damage;}

  private:
	  float damage;
};

#endif /* WEAPON_H */