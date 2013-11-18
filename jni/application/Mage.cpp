#include "Mage.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_)
  : Player(position_)
{
  max_hp = 100.0f;
  hp = max_hp;
}

void Mage::render() const
{
}

Weapon* Mage::range()
{
  return NULL;
}

void Mage::spc_skill()
{
}

Mage::~Mage()
{
}