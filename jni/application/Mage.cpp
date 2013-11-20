#include "Mage.h"
#include "Magic.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_,
           const int &uid_,
           const Team &team_)
: Player(position_, uid_, 80.0f, 100.0f, team_, "mage_")
{}

void Mage::render() const {
	Player::render();
}

Weapon* Mage::range() {
  Weapon* projectile = nullptr;
  if (can_attack()) {
    projectile = new Magic(calc_weapon_pos(), get_facing(), get_team());
    set_cannot_attack();
  }
  return projectile;
}

void Mage::spc_skill()
{
}
