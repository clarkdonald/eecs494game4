#include "Mage.h"
#include "Magic.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_, const int &uid_)
: Player(position_, uid_, 80.0f, 100.0f)
{}

void Mage::render() const {
	//Game_Object::render("sprite_downrun");
	Player::render();
}

Weapon* Mage::range() {
  Weapon* projectile = nullptr;
  if(can_attack()) {
    Point2f pos = calc_weapon_pos();
    projectile = new Magic(pos, get_facing());
    set_cannot_attack();
  }
  return projectile;
}

void Mage::spc_skill()
{
}
