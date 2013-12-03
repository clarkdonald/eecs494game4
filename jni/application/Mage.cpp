#include "Mage.h"
#include "Magic.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_,
           const int &uid_,
           const Team &team_)
: Player(position_, uid_, 80.0f, 100.0f, team_, "mage_", 0.5f), heal_circle(nullptr)
{}

void Mage::render() const {
	Player::render();
}

Weapon* Mage::range() {
  Weapon* projectile = nullptr;
  if (can_attack()) {
    projectile = new Magic(calc_weapon_pos(), get_facing(), get_team());
    start_attack_timer();
  }
  return projectile;
}

void Mage::spc_skill(bool pressed)
{
	if(pressed && !heal_circle) {
		heal_circle = new Heal_Circle(get_position());
		disable_attack();
	}
	else if(!pressed && heal_circle){
		delete heal_circle;
		heal_circle = nullptr;
		enable_attack();
	}
}

void Mage::move_x(const float &mag, const float &timestep, bool first_time) 
{
	if(heal_circle && first_time)
	{
		Point2f circle_pos = heal_circle->get_position();
    circle_pos.x += HEAL_CIRCLE_SPEED * timestep * mag;
    heal_circle->set_position(circle_pos);
	}
	else
		Player::move_x(mag, timestep, first_time);
}

void Mage::move_y(const float &mag, const float &timestep, bool first_time) 
{
	if(heal_circle && first_time)
	{
		Point2f circle_pos = heal_circle->get_position();
    circle_pos.y += HEAL_CIRCLE_SPEED * timestep * mag;
    heal_circle->set_position(circle_pos);
	}
	else
		Player::move_y(mag, timestep, first_time);
}

void Mage::render_extras() {
	if(heal_circle)
		heal_circle->render();
}
