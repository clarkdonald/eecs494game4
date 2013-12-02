//
//  Game_State.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Weapon.h"
#include "Percent_Bar.h"
#include "Object_Info.h"
#include "Utility.h"
#include <zenilib.h>
#include <string>
#include <map>
#include <list>
#include <vector>

class Control;
class Terrain;
class Atmosphere;
class Environment;
class Player;
class Spawn_Menu;
class Npc;
class Crystal;

struct Player_Wrapper {
  Player_Wrapper(Player *player_, const int &uid_);
  ~Player_Wrapper();
  Player* player;
  int uid;  
};

struct Player_Info {
  Player_Info(const Zeni::Point2f &start_position_, const Team &team_, Spawn_Menu * spawn_menu_);
  ~Player_Info();
  Controls controls;
  Percent_Bar health_bar;
  Percent_Bar crystal_bar;
  Object_Info crystal_info;
  Zeni::Point2f start_position;
  Spawn_Menu * spawn_menu;
  Team team;

	// code for main menu selection
	bool up_axis_released;
	bool down_axis_released;

  Zeni::Chronometer<Zeni::Time> deposit_crystal_timer;

};

class Game_State {
  public:
    Game_State(const std::string &file_);
    
    ~Game_State();
    
    void on_push();
    
    void on_pop();
        
    void perform_logic();
    
    void render();
        
    bool is_gameover() const {return gameover;}

    void execute_controller_code(const Zeni::Zeni_Input_ID &id,
                                 const float &confidence,
                                 const int &action);
    
  private:  
    void clear();
  
    void respawn_crystal();

	  void render_all(Player_Wrapper * player_wrapper);

    void render_spawn_menu(Player_Wrapper * player_wrapper);
  
    void create_tree(const Zeni::Point2f &position);
  
    void create_house(const Zeni::Point2f &position);
  
    void load_map(const std::string &file_);
    
    Zeni::Time_HQ time_passed;
    //Zeni::Chronometer<Zeni::Time> shooting_timer;
    std::list<Terrain*> terrains;
    std::list<Environment*> environments;
    std::list<Environment*> collidable_environments;
    std::list<Atmosphere*> atmospheres;
    std::list<Terrain*> grasss;
    std::list<Player_Wrapper*> player_wrappers;
    std::vector<Player_Info*> player_infos;
    std::list<Weapon*> projectiles;
    std::list<Weapon*> melees;
    std::list<Npc*> npcs;
    std::list<Crystal*> crystals;
    std::vector<Zeni::Point2f> crystal_locations;
    std::map<Team, unsigned int> scores;
    int total_num_crystals;
    int crystals_in_play;
    bool gameover;
    Dimension dimension;
    std::vector<std::pair<Zeni::Point2i, Zeni::Point2i> (*)()> screen_coord_map;
    Zeni::Vertex_Buffer *vbo_ptr_floor;
    Zeni::Vertex_Buffer *vbo_ptr_lower;
    Zeni::Vertex_Buffer *vbo_ptr_middle;
};

#endif /* GAME_STATE_H */