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

#define MAX_SPD 75.0f

class Player : public Game_Object {
  public:
	  Player(const Zeni::Point2f &position_, const int &uid_);
    virtual ~Player() {}

    virtual void render() const = 0;
  
    void move_y(const float, const float);
    void move_x(const float, const float);
	  void turn_to_face(const float);

    virtual Weapon* melee(const float) {return NULL;}	// sword
    virtual Weapon* range(const float) {return NULL;}  // arrow, fireball

	  virtual void spc_skill() = 0; // special class-specific attack

	  void take_dmg(float);
	  void die();

    float get_hp_pctg();
    unsigned int get_crystals_held();
    float get_facing();

	  void pick_up_crystal();
	  void drop_crystal();
  
    const int & get_uid() const {return uid;}

  private:

  protected:
	  float facing;

	  float hp;
    float max_hp;
	  unsigned int n_crystals;
    int uid;

    float std_cd; // standard attack cooldown
    float spc_cd; // special attack cooldown

    bool can_attack;
};

#endif /* PLAYER_H */
