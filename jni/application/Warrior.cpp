#include "Warrior.h"
#include "Sword.h"

using namespace Zeni;
using namespace std;

Warrior::Warrior(const Zeni::Point2f &position_,
                 const int &uid_,
                 const Team &team_)
: Player(position_, uid_, 120.0f, 200.0f, team_, "warrior_", 0.4f, 5.0f)
{}

void Warrior::render() const {
	Player::render();
}

Weapon* Warrior::melee() {
  return melee(get_facing());
}

Weapon* Warrior::melee(const float &direction) {
  Weapon* sword = nullptr;
  if (can_attack()) {
    sword = new Sword(calc_sword_pos(direction), direction, get_team(), this);
    start_attack_timer();
    weapon = sword;
  }
  return sword;
}

void Warrior::warrior_spc_skill(bool pressed)
{
}
