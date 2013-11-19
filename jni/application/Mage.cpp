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
    Point2f pos = get_position();
    Vector2f size = get_size();

    pos += Vector2f(size.magnitude() * cos(facing), size.magnitude() * sin(facing)); // top left of magic image

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