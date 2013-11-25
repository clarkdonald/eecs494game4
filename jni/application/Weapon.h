#ifndef WEAPON_H
#define WEAPON_H

#include "Game_Object.h"
#include "Utility.h"

class Weapon : public Game_Object {
  public:
	  Weapon(const Zeni::Point2f &position_,
           const float &damage_,
           const Team& team_,
           const Zeni::Vector2f &size_ = OBJECT_SIZE);
  
    virtual ~Weapon() = 0;

    virtual void update(const float) {}
  
	  virtual void render() const = 0;
  
    const Team & get_team() const {return team;}

    const float & get_damage() const {return damage;}

    virtual bool animation_over() {return false;}

    Zeni::Chronometer<Zeni::Time> animation_timer;

  private:
	  float damage;
    Team team;
};

#endif /* WEAPON_H */