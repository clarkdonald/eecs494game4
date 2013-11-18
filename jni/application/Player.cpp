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
	  hp(MAX_HP),
	  n_crystals(0),
	  equipped(NULL)
{
}

void Player::handle_inputs(const Controls input, const float timestep)
{

}

void Player::move_forward(const float timestep)
{
	Point2f pos = get_position();
	pos.y += MAX_SPD * timestep;
	set_position(pos);
}

void Player::move_right(const float timestep)
{
	Point2f pos = get_position();
	pos.x += MAX_SPD * timestep;
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
	while(n_crystals > 0)
		drop_crystal();

	// start spawn menu?
}

void Player::get_crystal()
{
	n_crystals++;
}

void Player::drop_crystal()
{
	if(n_crystals > 0)
		n_crystals--;

	// add crystal to some global render queue?
}