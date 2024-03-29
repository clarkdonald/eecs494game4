//
//  Player.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Player.h"
#include "Crystal.h"
#include <string>

using namespace Zeni;
using namespace std;

Player::Player(const Point2f &position_,
               const int &uid_,
               const float &speed_,
               const float &max_hp_,
               const Team &team_,
							 const String& sprite_prefix_,
							 const float& attack_limit_,
               const float& sp_attack_limit_,
               const Vector2f &size_)
: Game_Object(position_, size_, RECTANGLE),
  weapon(nullptr),
  shield(nullptr),
  speed(speed_),
  facing(Global::pi_over_two),
  max_hp(max_hp_),
  hp(max_hp_),
  attack_limit(attack_limit_),
  n_crystals(0),
  uid(uid_),
  attackable(true),
  submerged(false),
  dodge_time(3.0f),
  dodging(false),
  respawn_time(0.0f),
  blink_timer(0.0f),
  blink(false),
  hit(false),
  player_direction(DOWN),
	sprite_distance_traveled(0.0f),
  sprite_frame(0),
  sprite_prefix(sprite_prefix_),
	partner(nullptr),
  sp_attack_limit(sp_attack_limit_),
  team(team_),
  attack_enabled(true),
  move_enabled(true)
{
  time_since_attack.start();
  //time_since_special.start();
}

Player::~Player() 
{
  if(weapon != nullptr)
    delete weapon;

  if(shield != nullptr)
    delete shield;
}

void Player::move_x(const float &mag, const float &timestep, bool first_time) {
	Point2f pos = get_position();
	pos.x += speed * timestep * mag;
	set_position(pos);

  if(weapon != nullptr)
  {
    Point2f wep_pos = weapon->get_position();
    wep_pos.x += speed * timestep * mag;
    weapon->set_position(wep_pos);
  }

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
  
  if(weapon != nullptr)
  {
    Point2f wep_pos = weapon->get_position();
    wep_pos.y += speed * timestep * mag;
    weapon->set_position(wep_pos);
  }
  
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

void Player::dodge() {
  if(dodge_time > 3.0f) {
    dodge_time = 0.0f;  
    dodging = true;
  }
}

void Player::update_dodge_timer(const float &timestep) { 
  dodge_time += timestep;
  if(dodge_time > 0.1f) {
    dodging = false;    
  }
}

void Player::update_respawn_timer(const float &timestep) {
  respawn_time += timestep;
}

bool Player::can_respawn() const { 
  return respawn_time > 5.0f; 
}

bool Player::touching_feet(const Game_Object &rhs) const {
  float distance = UNIT_LENGTH / 2.0f;
  float centerX = get_position().x + (get_size().x / 2.0f);
  float bottomY = get_position().y + (get_size().y);
  float rhsCenterX = rhs.get_position().x + (rhs.get_size().x / 2.0f);
  float rhsCenterY = rhs.get_position().y + (rhs.get_size().y / 2.0f);
  
  if ((fabs(centerX - rhsCenterX) < distance) &&
      (fabs(bottomY - rhsCenterY) < distance))
  {
    return true;
  }
  return false;
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
  if ((hp -= dmg) <= 0.0f) {
    hp = 0.0f;
    // Just died so we need to restart the spawn timer
    respawn_time = 0.0f;
  } else {
    hit = true;
    blink = true;
    blink_timer = 0.0f;
  }
}

void Player::restore_health(const float& value)
{
	hp += value;
	if(hp > max_hp)
		hp = max_hp;
}


void Player::update_blink_timer(const float &timestep) { 
  if (hit) {
    blink_timer += timestep;
    if (blink_timer < 0.05f)
      blink = true;    
    else if (blink_timer <  0.1f)
      blink = false;
    else if (blink_timer < 0.15f)
      blink = true;
    else {
      hit = false;
      blink = false;
      blink_timer = 0.0f;
    }
  }  
}

void Player::kill() {
  hp = 0.0f;
  //respawn_time = 0.0f;
  n_crystals = 0;
}

float Player::get_hp_pctg() const {
  return hp/max_hp;
}

void Player::start_attack_timer()
{
	time_since_attack.reset();
}

void Player::start_special_timer()
{
	time_since_special.start();
}

void Player::stop_special_timer()
{
    time_since_special.stop();
    time_since_special.reset();
}

void Player::start_stun_timer()
{
	stun_timer.start();
}

bool Player::is_stunned()
{
  bool is_stun = false;
  if (stun_timer.is_running())
  {
    is_stun = stun_timer.seconds() < STUN_TIME;
    if (!is_stun)
    {
      stun_timer.stop();
      stun_timer.reset();
    }
  }
  return is_stun;
}

bool Player::can_use_special()
{
  bool can_use = true;
  if (time_since_special.is_running())
  {
    can_use = time_since_special.seconds() > sp_attack_limit;
    if(can_use)
    {
      stop_special_timer();
    }
  }
  return can_use && attack_enabled;
}

void Player::pick_up_crystal() {
	play_sound("gempickup");
	++n_crystals;
  restore_health(50);
}

void Player::drop_crystal() {
	if (n_crystals > 0) --n_crystals;
}

Point2f Player::calc_weapon_pos(const float &direction) {
    Point2f pos = get_center();
    Vector2f size = get_size();
    // Offset for how far away from player to shoot
    pos += Vector2f(size.magnitude() * 0.2f * cos(direction),
                    size.magnitude() * 0.2f * sin(direction));
    // Offset for centering the weapon wrt player's center
    pos -= (SMALL_SIZE / 2);
    return pos;
}

Point2f Player::calc_sword_pos(const float &direction) {
    Point2f pos = get_center();
    Vector2f size = get_size();
    // Offset for how far away from player to shoot
    pos += Vector2f(size.magnitude() * 0.3f * cos(direction),
                    size.magnitude() * 0.3f * sin(direction));
    // Offset for centering the sword's HANDLE wrt player's center
    pos -= (OBJECT_SIZE / 2);
    return pos;
}

Point2f Player::calc_shield_pos() {
    Point2f pos = get_center();
    Vector2f size = get_size();
    // Offset for how far away from player to shoot
    pos += Vector2f(size.magnitude() * 0.7f * cos(facing),
                    size.magnitude() * 0.7f * sin(facing));
    // Offset for centering the weapon wrt player's center
    pos -= (OBJECT_SIZE / 2);
    return pos;
}

void Player::render() const {
	if(is_dead() || blink) return;
  // render player

	String str;

  Point2f crystal_pos = Point2f(get_position().x, get_position().y - 16.0f);
	Crystal* crystal = new Crystal(crystal_pos, Vector2f(8.0f, 8.0f));
	for(int k = 0; k < n_crystals; k++)
	{
		crystal -> render();
		crystal -> set_position(Point2f(crystal->get_position().x + 6.0f, crystal->get_position().y));
	}

	if(dodging) return;

	switch(team)
	{
		case RED:
			str = "red_";
			break;
		case BLUE:
			str = "blue_";
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
  else if(sprite_prefix == "warrior_" &&
          weapon != nullptr)
  {
    switch(player_direction)
		{
			case UP:
				str += "attackup";
				Game_Object::render(str);
				break;
			case DOWN:
				str += "attackdown";
				Game_Object::render(str);
				break;
			case LEFT:
				str += "attackleft";
				Game_Object::render(str);
				break;
			case RIGHT:
				str += "attackright";
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