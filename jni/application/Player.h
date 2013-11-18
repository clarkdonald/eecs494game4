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
  
	  void handle_inputs(const Controls, const float);

    virtual Weapon* melee() {return NULL;}	// sword
    virtual Weapon* range() {return NULL;}  // arrow, fireball

	  virtual void spc_skill() = 0; // special class-specific attack

	  void take_dmg(float);
	  void die();

    float get_hp();
    unsigned int get_crystals_held();

	  void pick_up_crystal();
	  void drop_crystal();
  
    const int & get_uid() const {return uid;}

  private:
	  void turn_to_face(const float);

  protected:
	  Weapon* equipped;
	  float facing;

	  float hp;
    float max_hp;
	  unsigned int n_crystals;
    int uid;
};

#endif /* PLAYER_H */
