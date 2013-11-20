#include "Warrior.h"
#include "Sword.h"

using namespace Zeni;
using namespace std;

Warrior::Warrior(const Zeni::Point2f &position_,
                 const int &uid_,
                 const Team &team_)
: Player(position_, uid_, 60.0f, 200.0f, team_, "")
{}

void Warrior::render() const {
	Player::render();
}

Weapon* Warrior::melee() {
  Weapon* sword = nullptr;
  if (can_attack()) {
    sword = new Sword(calc_weapon_pos(), get_facing(), get_team());
    set_cannot_attack();
  }
  return sword;
}

void Warrior::spc_skill()
{
}
