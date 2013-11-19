#include "Sword.h"

using namespace Zeni;
using namespace std;

Sword::Sword(const Zeni::Point2f &position_, const float &theta)
  : Weapon(position_),
    dir(theta)
{
  damage = 50.0f;
}

void Sword::render() const
{
  Game_Object::render("arrow", Color(), dir + Global::pi_over_two); // TODO: find sword.png and get a corrected angle
}

Sword::~Sword()
{
}