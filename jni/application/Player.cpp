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

Player::Player(const Point2f &position_, const int &uid_, const float &max_hp_)
: Game_Object(position_),
  facing(Global::pi_over_two),
  max_hp(max_hp_),
  hp(max_hp_),
  n_crystals(0),
  uid(uid_),
  attackable(true)
{}

Player::~Player() {}

void Player::move_x(const float &mag, const float &timestep) {
	Point2f pos = get_position();
	pos.x += MAX_SPD * timestep * mag;
	set_position(pos);
}

void Player::move_y(const float &mag, const float &timestep) {
	Point2f pos = get_position();
	pos.y += MAX_SPD * timestep * mag;
	set_position(pos);
}

void Player::turn_to_face(const float &theta) {
	facing = theta;
}

void Player::take_dmg(const float &dmg) {
  if ((hp -= dmg) < 0.0f) {
    hp = 0.0f;
    die();
  }
}

void Player::die() {
	while (n_crystals != 0) drop_crystal();
	// TODO: start spawn menu?
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
	if (n_crystals != 0) n_crystals--;
	//TODO: add crystal to some global render queue?
}

Point2f Player::calc_weapon_pos() {
    Point2f pos = get_position();
    Vector2f size = get_size();
    pos += Vector2f(size.magnitude() * 0.9f * cos(facing), size.magnitude() * 0.9f * sin(facing));
    return pos;
}