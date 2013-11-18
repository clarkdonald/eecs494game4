#include "Warrior.h"

using namespace Zeni;
using namespace std;

Warrior::Warrior(const Zeni::Point2f &position_)
  : Player(position_)
{
  max_hp = 200.0f;
  hp = max_hp;


}

void Warrior::render()
{
	
}

Weapon* Warrior::melee()
{
  return equipped;
}

void Warrior::spc_attack()
{
}

Warrior::~Warrior()
{
}