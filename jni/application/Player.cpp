//
//  Player.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Player.h"

using namespace Zeni;
using namespace std;

Player::Player(const Zeni::Point2f &position_, const int &uid_)
: Game_Object(position_),
  facing(Global::pi_over_two),
  n_crystals(0),
  uid(uid_),
  can_attack(true)
{}

void Player::move_x(const float mag, const float timestep)
{
	Point2f pos = get_position();
	pos.x += MAX_SPD * timestep * mag;
	set_position(pos);
}

void Player::move_y(const float mag, const float timestep)
{
	Point2f pos = get_position();
	pos.y += MAX_SPD * timestep * mag;
	set_position(pos);
}

void Player::turn_to_face(const float theta)
{
	facing = theta;
}

void Player::take_dmg(float dmg)
{
	hp -= dmg;
	if(hp <= 0)
		die();
}

void Player::die()
{
	while(n_crystals != 0)
		drop_crystal();

	// start spawn menu?
}

float Player::get_hp_pctg()
{
  return hp/max_hp;
}

unsigned int Player::get_crystals_held()
{
  return n_crystals;
}

float Player::get_facing()
{
  return facing;
}

void Player::set_can_attack()
{
  can_attack = true;
}

void Player::pick_up_crystal()
{
	n_crystals++;
}

void Player::drop_crystal()
{
	if(n_crystals != 0)
		n_crystals--;

	// add crystal to some global render queue?
}


Point2f Player::calc_weapon_pos()
{
    Point2f pos = get_position();
    Vector2f size = get_size();

    pos += Vector2f(size.magnitude() * 0.9f * cos(facing), size.magnitude() * 0.9f * sin(facing)); // top left of magic image

    return pos;
}