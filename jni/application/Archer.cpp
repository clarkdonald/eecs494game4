#include "Archer.h"
#include "Arrow.h"
#include "Stun_Arrow.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_,
               const int &uid_,
               const Team &team_)
: Player(position_, uid_, 100.0f, 450.0f, team_, "archer_", .5f, 8.0f)
{}

void Archer::render() const {
  Player::render();
}

Weapon* Archer::range() {
  return range(get_facing());
}

Weapon* Archer::range(const float &direction)
{
  Weapon* projectile = nullptr;
  if (can_attack()) {
		play_sound("bow", 1.0f, .1f);
    projectile = new Arrow(calc_weapon_pos(direction), direction, get_team());
    start_attack_timer();
  }
  return projectile;
}

Weapon* Archer::archer_spc_skill() {
  return archer_spc_skill(get_facing());
}

Weapon* Archer::archer_spc_skill(const float &direction)
{
  Weapon* stun_arrow = nullptr;
  if (can_use_special()) {
    stun_arrow = new Stun_Arrow(calc_weapon_pos(direction), direction, get_team());
    start_special_timer();
  }
  return stun_arrow;
}
