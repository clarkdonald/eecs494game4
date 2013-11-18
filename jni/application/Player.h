//
//  Player.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Game_Object.h"
#include "Weapon.h"

#define MAX_HP 100.0f
#define MAX_SPD 20.0f

class Player : public Game_Object {
  public:
	Player(const Zeni::Point2f &position_);
    virtual ~Player() = 0;

    virtual void render() = 0;
  
	void handle_inputs(const Controls, const float);

	void move_forward(const float);
	void move_right(const float);
	void turn_to_face(const float);

	virtual Weapon* std_attack() = 0;	  // sword, arrow, fireball
	virtual void spc_skill() = 0; // special class-specific attack

	void take_dmg(float);
	void die();

	void get_crystal();
	void drop_crystal();

  private:
	float facing;

	float hp;
	int n_crystals;
};

#endif /* PLAYER_H */
