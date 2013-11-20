#include "Archer.h"
#include "Arrow.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_,
               const int &uid_,
               const Team &team_)
: Player(position_, uid_, 100.0f, 150.0f, team_)
{}

void Archer::render() const {
	Game_Object::render("downidle");
}

Weapon* Archer::range()
{
  Weapon* projectile = nullptr;
  if (can_attack()) {
    projectile = new Arrow(calc_weapon_pos(), get_facing(), get_team());
    set_cannot_attack();
  }
  return projectile;
}

void Archer::spc_skill()
{
}
