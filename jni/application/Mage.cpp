#include "Mage.h"
#include "Magic.h"

using namespace Zeni;
using namespace std;

Mage::Mage(const Zeni::Point2f &position_,
           const int &uid_,
           const Team &team_)
: Player(position_, uid_, 80.0f, 300.0f, team_, "mage_", 0.5f, 5.0f), heal_circle(nullptr)
{heal_duration_timer.start();}

void Mage::render() const {
	Player::render();
}

Weapon* Mage::range() {
  return range(get_facing());
}

Weapon* Mage::range(const float &direction) {
  Weapon* projectile = nullptr;
  if (can_attack()) {
		play_sound("magic", 1.0f, .1f);
    projectile = new Magic(calc_weapon_pos(direction), direction, get_team());
    start_attack_timer();
  }
  return projectile;
}

Heal_Circle* Mage::mage_spc_skill(bool pressed, const float& time_step)
{
	if(pressed && !heal_circle && can_use_special()) {
		heal_circle = new Heal_Circle(Point2f(get_position().x - 80, get_position().y - 72), get_team());
		heal_duration_timer.reset();
		disable_attack();
		disable_movement();
	}
	else if(pressed && heal_circle) {
		restore_health(time_step * 50);
		if(heal_circle -> touching(*get_partner()))
    {
      if(!get_partner()->is_dead())
			  get_partner() -> restore_health(time_step * 50);
    }
	}
	if((heal_duration_timer.seconds() > 3 || !pressed) && heal_circle){

		delete heal_circle;
		heal_circle = nullptr;
		enable_attack();
		enable_movement();
    start_special_timer();
	}
  return heal_circle;
}

void Mage::move_x(const float &mag, const float &timestep, bool first_time) 
{
	/*if(heal_circle && first_time)
	{
		Point2f circle_pos = heal_circle->get_position();
    circle_pos.x += HEAL_CIRCLE_SPEED * timestep * mag;
    heal_circle->set_position(circle_pos);
	}
	else*/
	if(can_move())
		Player::move_x(mag, timestep, first_time);
}

void Mage::move_y(const float &mag, const float &timestep, bool first_time) 
{
	/*if(heal_circle && first_time)
	{
		Point2f circle_pos = heal_circle->get_position();
    circle_pos.y += HEAL_CIRCLE_SPEED * timestep * mag;
    heal_circle->set_position(circle_pos);
	}
	else*/
	if(can_move())
		Player::move_y(mag, timestep, first_time);
}

void Mage::render_extras() {
	if(heal_circle)
		heal_circle->render();
}
