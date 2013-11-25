//
//  Player.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Player.h"
#include <string>

using namespace Zeni;
using namespace std;

Player::Player(const Point2f &position_,
               const int &uid_,
               const float &speed_,
               const float &max_hp_,
               const Team &team_,
							 const String& sprite_prefix_)
: Game_Object(position_),
  speed(speed_),
  facing(Global::pi_over_two),
  max_hp(max_hp_),
  hp(max_hp_),
  n_crystals(0),
  uid(uid_),
  attackable(true),
  player_direction(DOWN),
	sprite_distance_traveled(0.0f),
	sprite_frame(0),
  team(team_),
	sprite_prefix(sprite_prefix_),
	submerged(false)
{}

Player::~Player() {}

void Player::move_x(const float &mag, const float &timestep, bool first_time) {
	Point2f pos = get_position();
	pos.x += speed * timestep * mag;
	set_position(pos);

	// code to anmimate movement
	if(first_time){
		sprite_distance_traveled += speed * timestep * abs(mag);

		if(mag >= 0.3f)
			player_direction = RIGHT;
		else if(mag <= -.3f)
			player_direction = LEFT;

		if(sprite_distance_traveled >= 20.0f) {
				sprite_distance_traveled = 0;
				sprite_frame++;
				if(sprite_frame == 4)
					sprite_frame = 0;
		}
	}
}

void Player::move_y(const float &mag, const float &timestep, bool first_time) {
	Point2f pos = get_position();
	pos.y += speed * timestep * mag;
	set_position(pos);

	// code to animate movement
	if(first_time) {
		sprite_distance_traveled += speed * timestep * abs(mag);
	
		if(mag >= 0.3f)
			player_direction = DOWN;
		else if(mag <= -.3f)
			player_direction = UP;

		if(sprite_distance_traveled >= 20.0f) {
				sprite_distance_traveled = 0;
				sprite_frame++;
				if(sprite_frame == 4)
					sprite_frame = 0;
		}
	}
}

void Player::turn_to_face(const float &theta) {
	facing = theta;

	float tempo = theta + Global::pi_over_two;
	if(tempo >= .7854f && tempo <= 2.356f)
		player_direction = RIGHT;
	else if(tempo >= 2.356f && tempo <= 3.927)
		player_direction = DOWN;
	else if(tempo >= 3.927 && tempo <= 5.498f)
		player_direction = LEFT;
	else
		player_direction = UP;
}

void Player::take_dmg(const float &dmg) {
  if ((hp -= dmg) < 0.0f) {
    hp = 0.0f;
    die();
  }
}

void Player::die() {
	while (n_crystals != 0) --n_crystals; 
}

void Player::kill() {
  hp = 0.0f;
}

float Player::get_hp_pctg() const {
  return hp/max_hp;
}

void Player::set_can_attack() {
  attackable = true;
}

void Player::set_cannot_attack() {
  attackable = false;
}

void Player::pick_up_crystal() {
	++n_crystals;
}

void Player::drop_crystal() {
	if (n_crystals != 0) --n_crystals;
}

Point2f Player::calc_weapon_pos() {
    Point2f pos = get_center();
    Vector2f size = get_size();
    // Offset for how far away from player to shoot
    pos += Vector2f(size.magnitude() * 0.2f * cos(facing),
                    size.magnitude() * 0.2f * sin(facing));
    // Offset for centering the weapon wrt player's center
    pos -= (SMALL_SIZE / 2);
    return pos;
}

void Player::render() const {
	if(is_dead()) return;
	String str;

	switch(team)
	{
		case WHITE:
			str = "blue_";
			break;
		case BLACK:
			str = "red_";
			break;
	}

	if(submerged)
	{
		switch(player_direction)
		{
			case UP:
				str += "upsubmerged";
				Game_Object::render(str);
				break;
			case DOWN:
				str += "downsubmerged";
				Game_Object::render(str);
				break;
			case LEFT:
				str += "leftsubmerged";
				Game_Object::render(str);
				break;
			case RIGHT:
				str += "rightsubmerged";
				Game_Object::render(str);
				break;
		}
	}
	else
	{
		str = sprite_prefix + str;
		switch(player_direction)
		{
			case UP:
				str += "uprun";
				str += to_string(sprite_frame + 1).c_str();
				Game_Object::render(str);
				break;
			case DOWN:
				str += "downrun";
				str += to_string(sprite_frame + 1).c_str();
				Game_Object::render(str);
				break;
			case LEFT:
				str += "leftrun";
				str += to_string(sprite_frame + 1).c_str();
				Game_Object::render(str);
				break;
			case RIGHT:
				str += "rightrun";
				str += to_string(sprite_frame + 1).c_str();
				Game_Object::render(str);
				break;
		}
	}
}