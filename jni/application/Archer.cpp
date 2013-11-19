#include "Archer.h"
#include "Arrow.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_, const int &uid_)
: Player(position_, uid_, 100.0f, 150.0f)
{}

void Archer::render() const {
	Game_Object::render("downidle");
}

Weapon* Archer::range()
{
  Weapon* projectile = nullptr;
  if (can_attack()) {
    Point2f pos = calc_weapon_pos();
    projectile = new Arrow(pos, get_facing());
    set_cannot_attack();
  }
  return projectile;
}

void Archer::spc_skill()
{
}
