#include "Warrior.h"

using namespace Zeni;
using namespace std;

Warrior::Warrior(const Zeni::Point2f &position_)
  : Player(position_)
{
}

void Warrior::render()
{
}

Weapon* Warrior::std_attack()
{
  return NULL;
}

void Warrior::spc_attack()
{
}

Warrior::~Warrior()
{
}