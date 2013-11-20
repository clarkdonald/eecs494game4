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

Player::Player(const Point2f &position_,
               const int &uid_,
               const float &speed_,
               const float &max_hp_,
               const Team &team_)
: Game_Object(position_),
  speed(speed_),
  facing(Global::pi_over_two),
  max_hp(max_hp_),
  hp(max_hp_),
  n_crystals(0),
  uid(uid_),
  attackable(true),
  team(team_)
{}

Player::~Player() {}

void Player::move_x(const float &mag, const float &timestep) {
	Point2f pos = get_position();
	pos.x += speed * timestep * mag;
	set_position(pos);
}

void Player::move_y(const float &mag, const float &timestep) {
	Point2f pos = get_position();
	pos.y += speed * timestep * mag;
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
	while (n_crystals != 0) --n_crystals;
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