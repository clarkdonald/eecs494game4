#include "Mage.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_)
  : Player(position_)
{
}

void Mage::render()
{
}

Weapon* Mage::range()
{
  return NULL;
}

void Mage::spc_attack()
{
}

Mage::~Mage()
{
}