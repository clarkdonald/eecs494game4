#include "Archer.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_)
  : Player(position_)
{
  max_hp = 150.0f;
  hp = max_hp;
}

void Archer::render() const
{
}

Weapon* Archer::range()
{
  return NULL;
}

void Archer::spc_skill()
{
}

Archer::~Archer()
{
}