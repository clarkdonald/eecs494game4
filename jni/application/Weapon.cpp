#include "Weapon.h"

using namespace Zeni;
using namespace std;

Weapon::Weapon(const Point2f &position_,
               const float &damage_,
               const Team& team_,
               const Vector2f &size_)
: Game_Object(position_, size_), damage(damage_), team(team_),
  stun_attack(false)
{}

Weapon::~Weapon() {}
