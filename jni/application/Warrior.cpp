#include "Warrior.h"
#include "Sword.h"

using namespace Zeni;
using namespace std;

Warrior::Warrior(const Zeni::Point2f &position_, const int &uid_)
  : Player(position_, uid_)
{
  max_hp = 200.0f;
  hp = max_hp;
}

void Warrior::render() const
{
	Game_Object::render("downidle");
}

Weapon* Warrior::melee()
{
  Weapon* sword = nullptr;
  if(can_attack)
  {
    Point2f pos = calc_weapon_pos();
    sword = new Sword(pos, facing);
    
    can_attack = false;
  }
  return sword;
}

void Warrior::spc_skill()
{
}

Warrior::~Warrior()
{
}