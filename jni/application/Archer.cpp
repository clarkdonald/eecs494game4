#include "Archer.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_)
  : Player(position_)
{
}

void Archer::render()
{
}

Weapon* Archer::range()
{
  return NULL;
}

void Archer::spc_attack()
{
}

Archer::~Archer()
{
}