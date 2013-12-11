#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"
#include <zenilib.h>

class Archer : public Player {
  public:
    Archer(const Zeni::Point2f &position_,
           const int &uid_,
           const Team &team_,
           const Zeni::Vector2f &size_ = OBJECT_SIZE);

    void render() const override;
  
    Weapon* range() override;

    Weapon* range(const float &direction) override;
  
    Weapon* archer_spc_skill() override;
  
    Weapon* archer_spc_skill(const float &direction) override;

		void set_can_attack();
		void set_cannot_attack();

    Zeni::String get_skill_str() const override {return "archer_skill"; }

private:
	Zeni::Chronometer<Zeni::Time> time_since_attack;
};

#endif /* ARCHER_H */