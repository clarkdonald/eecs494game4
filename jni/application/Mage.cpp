#include "Mage.h"
#include "Magic.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_, const int &uid_)
  : Player(position_, uid_)
{
  max_hp = 100.0f;
  hp = max_hp;
}

void Mage::render() const
{
	Game_Object::render("downidle");
}

Weapon* Mage::range()
{
  Weapon* projectile = nullptr;
  if(can_attack)
  {
    Point2f pos = calc_weapon_pos();
    projectile = new Magic(pos, facing);
    
    can_attack = false;
  }
  return projectile;
}

void Mage::spc_skill()
{
}

Mage::~Mage()
{
}