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

Player::Player(const Zeni::Point2f &position_)
	: Game_Object(position_),
	  n_crystals(0)
{
}

void Player::handle_inputs(const Controls input, const float timestep)
{
	Point2f pos = get_position();
	pos.y += MAX_SPD * timestep * input.move_y;
	pos.x += MAX_SPD * timestep * input.move_x;
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

float Player::get_hp()
{
  return hp;
}

unsigned int Player::get_crystals_held()
{
  return n_crystals;
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