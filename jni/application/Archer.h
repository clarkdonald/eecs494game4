#ifndef ARCHER_H
#define ARCHER_H

#include "Player.h"
#include <zenilib.h>

class Archer : public Player {
  public:
    Archer(const Zeni::Point2f &position_,
           const int &uid_,
           const Team &team_);

    void render() const override;

    Weapon* range() override;
  
    Weapon* archer_spc_skill() override;

		void set_can_attack();
		void set_cannot_attack();
private:
	Zeni::Chronometer<Zeni::Time> time_since_attack;
};

#endif /* ARCHER_H */