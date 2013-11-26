#include "Archer.h"
#include "Arrow.h"

using namespace Zeni;
using namespace std;

Archer::Archer(const Zeni::Point2f &position_,
               const int &uid_,
               const Team &team_)
: Player(position_, uid_, 100.0f, 150.0f, team_, "archer_", .5f)
{}

void Archer::render() const {
  Player::render();
}

Weapon* Archer::range()
{
  Weapon* projectile = nullptr;
  if (can_attack()) {
    projectile = new Arrow(calc_weapon_pos(), get_facing(), get_team());
    start_attack_timer();
  }
  return projectile;
}

void Archer::spc_skill()
{

}
