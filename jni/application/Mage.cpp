#include "Mage.h"

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