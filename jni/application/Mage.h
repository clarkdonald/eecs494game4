#ifndef MAGE_H
#define MAGE_H

#include "Player.h"
#include "Heal_Circle.h"

#define HEAL_CIRCLE_SPEED 400

class Mage : public Player {
  public:
    Mage(const Zeni::Point2f &position_,
         const int &uid_,
         const Team &team_);

    void render() const override;

		void render_extras();

		void move_y(const float &, const float &, bool) override;
  
    void move_x(const float &, const float &, bool) override;

    Weapon* range() override;
  
    void mage_spc_skill(bool pressed) override;

private:
	Heal_Circle* heal_circle;
};

#endif /* MAGE_H */