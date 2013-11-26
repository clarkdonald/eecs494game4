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
#include "Utility.h"
#include "Weapon.h"

class Player : public Game_Object {
  public:
	  Player(const Zeni::Point2f &position_,
           const int &uid_,
           const float &speed_,
           const float &max_hp_,
           const Team &team_,
					 const Zeni::String& sprite_prefix_,
					 const float& attack_limit_);
  
    virtual ~Player() = 0;

    virtual void render() const = 0;
  
    void move_y(const float &, const float &, bool);
  
    void move_x(const float &, const float &, bool);

    void dodge();

    void update_dodge_timer(const float &timestep);

    bool is_dodging() {return dodging;};

    bool touching_feet(const Game_Object &rhs) const;
  
	  void turn_to_face(const float &);

    virtual Weapon* melee() {return nullptr;}	// sword
  
    virtual Weapon* range() {return nullptr;}  // arrow, fireball

	  virtual void spc_skill() = 0; // special class-specific attack

	  void take_dmg(const float &);
  
    bool is_dead() const {return hp <= 0.0f;}
  
	  void die();
  
    bool is_depositting_crystal() const;    
  
    void deposit_crystal();
  
    const Team & get_team() const {return team;}

    void kill();

    float get_hp_pctg() const;
    
    const unsigned int & get_crystals_held() const {return n_crystals;}
  
    bool has_crystal() const {return n_crystals > 0;}
  
    const float & get_facing() const {return facing;}

		void set_submerged(bool value) {submerged = value;}

		void start_attack_timer();

    void pick_up_crystal();
  
	  void drop_crystal();
  
    const int & get_uid() const {return uid;}
  
    void remove_weapon() {weapon = nullptr;}
  protected:
		virtual bool can_attack() const {return time_since_attack.seconds() > attack_limit;}
    Weapon* weapon;
    Zeni::Point2f calc_weapon_pos();
    Zeni::Point2f calc_sword_pos();

  private:
    float speed;
    float facing;
    float max_hp;
    float hp;
		float attack_limit;
    unsigned int n_crystals;
    int uid;
    bool attackable;
		bool submerged;    
    float dodge_time;
    bool dodging;
		enum Player_Direction {LEFT, RIGHT, UP, DOWN};
		Player_Direction player_direction;
		float sprite_distance_traveled;
		int sprite_frame;
		Zeni::String sprite_prefix;
    Team team;
		Zeni::Chronometer<Zeni::Time> time_since_attack;
};

#endif /* PLAYER_H */
