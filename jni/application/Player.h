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

#define STUN_TIME 2.0f

class Heal_Circle;

class Player : public Game_Object {
  public:
	  Player(const Zeni::Point2f &position_,
           const int &uid_,
           const float &speed_,
           const float &max_hp_,
           const Team &team_,
					 const Zeni::String& sprite_prefix_,
					 const float& attack_limit_,
           const float& sp_attack_limit_,
           const Zeni::Vector2f &size_ = OBJECT_SIZE);
  
    virtual ~Player() = 0;

    virtual void render() const = 0;

		virtual void render_extras() {}
  
    virtual void move_y(const float &, const float &, bool);
  
    virtual void move_x(const float &, const float &, bool);

    void dodge();

    void update_dodge_timer(const float &timestep);

    bool can_use_dodge() const { return dodge_time > 3.0f; }     

    bool is_dodging() {return dodging;}

    float get_dodge_percentage() const { return dodge_time / 3.0f; }

    bool can_respawn() const;

    void reset_respawn_time() { respawn_time = 6.0f; }

    float get_spawn_time() const { return respawn_time; }

    void update_respawn_timer(const float &timestep);

    bool touching_feet(const Game_Object &rhs) const;
  
	  void turn_to_face(const float &);
  
    virtual Weapon* melee() {return nullptr;}
  
    virtual Weapon* range() {return nullptr;}

    virtual Weapon* melee(const float &direction) {return nullptr;}	// sword
  
    virtual Weapon* range(const float &direction) {return nullptr;}  // arrow, fireball

    virtual bool can_use_special();
    void stop_special_timer();
    
    float get_special_attck_percentage() const {return time_since_special.seconds() / sp_attack_limit;}

    virtual Heal_Circle* mage_spc_skill(bool pressed, const float& time_step) {return nullptr;} // special class-specific attack
    virtual Weapon* archer_spc_skill(const float &direction) {return nullptr;} // special class-specific attack
    virtual Weapon* archer_spc_skill() {return nullptr;} // special class-specific attack
    virtual Weapon* warrior_spc_skill() {return nullptr;} // special class-specific attack

	  void take_dmg(const float &);
		
		void restore_health(const float&);

    void update_blink_timer(const float &timestep);
  
    bool is_dead() const {return hp <= 0.0f;}	  
  
    bool is_depositting_crystal() const;   
  
    void deposit_crystal();
  
    const Team & get_team() const {return team;}

    void kill();

    float get_hp_pctg() const;
    
    const unsigned int & get_crystals_held() const {return n_crystals;}
  
    bool has_crystal() const {return n_crystals > 0;}
  
    const float & get_facing() const {return facing;}

		void set_submerged(bool value) {submerged = value;}
    bool is_submerged() {return submerged;}

		void start_attack_timer();
		void start_special_timer();
    void start_stun_timer();

    bool is_stunned();

    void pick_up_crystal();
  
	  void drop_crystal();

		void set_partner(Player* partner_ptr) {partner = partner_ptr;}
  
    const int & get_uid() const {return uid;}
  
    void remove_weapon() {weapon = nullptr;}
    void remove_shield() {shield = nullptr;}

		Player* get_partner() {return partner;}

    virtual Zeni::String get_skill_str() const = 0;

		bool can_move() {return move_enabled;}
		void disable_movement() {move_enabled = false;}
		void enable_movement() {move_enabled = true;}

		void disable_attack() {attack_enabled = false;}
		void enable_attack() {attack_enabled = true;}

    Weapon* get_weapon() {return weapon;}
    Weapon* get_shield() {return shield;}
  
  protected:
		virtual bool can_attack() const {return attack_enabled && time_since_attack.seconds() > attack_limit;}
    
    Weapon* weapon;
    Weapon* shield;
    Zeni::Point2f calc_weapon_pos(const float &direction);
    Zeni::Point2f calc_sword_pos(const float &direction);
    Zeni::Point2f calc_shield_pos();

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

    float respawn_time;    

    float blink_timer;
    bool blink;
    bool hit;

		enum Player_Direction {LEFT, RIGHT, UP, DOWN};
		Player_Direction player_direction;
		float sprite_distance_traveled;
		int sprite_frame;
		Zeni::String sprite_prefix;
		Player* partner;
		Zeni::Chronometer<Zeni::Time> time_since_attack;
		Zeni::Chronometer<Zeni::Time> time_since_special;
		Zeni::Chronometer<Zeni::Time> stun_timer;
    float sp_attack_limit;
    Team team;
    bool attack_enabled;
    bool move_enabled;
};

#endif /* PLAYER_H */
