#include "Sword.h"

using namespace Zeni;
using namespace std;

Sword::Sword(const Zeni::Point2f &position_,
             const float &theta_,
             const Team& team_)
: Weapon(position_, 50.0f, team_),
  dir(theta_)
{
}

void Sword::render() const {
  Game_Object::render("sword",
                      Color(),
                      dir + Global::pi_over_two); // TODO: find sword.png and get a corrected angle
}
